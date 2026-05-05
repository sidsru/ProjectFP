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

export async function registerAccount({ UserID, password, nickname }) {
  const connection = await pool.getConnection();

  try {
    await connection.beginTransaction();

    const existingAccount = await findAccountByUserID(UserID, connection);

    if (existingAccount) {
      throw new Error("DUPLICATED_USER_ID");
    }

    const passwordHash = await bcrypt.hash(password, 10);

    const accountId = await createAccount(
      {
        UserID,
        passwordHash,
        accountStatus: "ACTIVE"
      },
      connection
    );

    const profileId = await createPlayerProfile(
      {
        accountId,
        nickname: nickname || UserID
      },
      connection
    );

    await createInventory(profileId, connection);

    await createDefaultCurrencies(profileId, connection);

    await connection.commit();

    const account = {
      account_id: accountId,
      UserID,
      account_status: "ACTIVE"
    };

    const profile = {
      profile_id: profileId,
      nickname: nickname || UserID,
      level: 1,
      exp: 0
    };

    const accessToken = createAccessToken(account);

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

export async function loginAccount({ UserID, password }) {
  const account = await findAccountByUserID(UserID);

  if (!account) {
    throw new Error("INVALID_LOGIN");
  }

  const isPasswordValid = await bcrypt.compare(
    password,
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