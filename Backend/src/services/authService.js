import bcrypt from "bcryptjs";
import jwt from "jsonwebtoken";
import pool from "../db.js";

import {
  findAccountByUserID,
  createAccount,
  updateLastLoginAt,
  createPlayerProfile,
  createInventory,
  createDefaultCurrencies,
  findProfileByAccountId
} from "../repositories/accountRepository.js";

function createAccessToken(account) {
  return jwt.sign(
    {
      accountId: account.account_id,
      userId: account.UserID
    },
    process.env.JWT_SECRET,
    {
      expiresIn: process.env.JWT_EXPIRES_IN || "1h"
    }
  );
}

export async function registerAccount({ UserID, Password }) {
  const connection = await pool.getConnection(); // 풀에서 DB연결을 가져옴

  try {
    await connection.beginTransaction();

    const existingAccount = await findAccountByUserID(UserID, connection); // 중복 아이디 확인 

    if (existingAccount) {
      throw new Error("DUPLICATED_USER_ID"); // 중복 아이디 발견으로 인해 오류를 던짐
    }

    const passwordHash = await bcrypt.hash(Password, 10); // 입력된 비밀 번호를 해쉬 값으로 변경하여 저장

    const accountId = await createAccount(
      {
        UserID,// 아이디
        passwordHash, //해쉬값으로 변경된 비밀번호
        accountStatus: "ACTIVE" // 접속을 확인
      },
      connection
    );

    const profileData = await createPlayerProfile(accountId, connection); // 프로필 생성

    await createInventory(profileData , connection); // 인벤토리 생성

    await createDefaultCurrencies(profileData, connection);

    await connection.commit();

    const account = {
      account_id: accountId,
      UserID,
      account_status: "ACTIVE"
    };

    const profile = {
      profile_id: profileData,
      level: 1,
      exp: 0
    };

    const accessToken = createAccessToken(account); // 토큰 생성

    return {
      accessToken, 
      account,
      profile
    };
  } catch (err) {
    await connection.rollback();
    throw err;
  } finally {
    connection.release();
  }
}

export async function loginAccount({ UserID, Password }) {
  const account = await findAccountByUserID(UserID);

  if (!account) {
    throw new Error("INVALID_LOGIN");
  }

  const isPasswordValid = await bcrypt.compare(
    Password,
    account.password_hash
  );

  if (!isPasswordValid) {
    throw new Error("INVALID_LOGIN");
  }

  if (account.account_status !== "ACTIVE") {
    throw new Error("ACCOUNT_BLOCKED");
  }

  await updateLastLoginAt(account.account_id);

  const profile = await findProfileByAccountId(account.account_id);

  const accessToken = createAccessToken(account);

  return {
    accessToken,
    account: {
      account_id: account.account_id,
      UserID: account.UserID,
      account_status: account.account_status
    },
    profile
  };
}