import pool from "../db.js";

function getExecutor(connection) {
  return connection || pool;
}

export async function findAccountByUserID(UserID, connection = null) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      account_id,
      UserID,
      password_hash,
      created_at,
      last_login_at,
      account_status
    FROM accounts
    WHERE UserID = ?
    LIMIT 1
    `,
    [UserID]
  );

  return rows[0] || null;
}

export async function createAccount(
  {
    UserID,
    passwordHash,
    accountStatus
  },
  connection = null
) {
  const db = getExecutor(connection);

  const [result] = await db.query(
    `
    INSERT INTO accounts (
      UserID,
      password_hash,
      account_status
    )
    VALUES (?, ?, ?)
    `,
    [UserID, passwordHash, accountStatus]
  );

  return result.insertId;
}

export async function updateLastLoginAt(accountId, connection = null) {
  const db = getExecutor(connection);

  await db.query(
    `
    UPDATE accounts
    SET last_login_at = CURRENT_TIMESTAMP
    WHERE account_id = ?
    `,
    [accountId]
  );
}

export async function createPlayerProfile(account_id, connection = null, nickname = null ) {
  const db = getExecutor(connection);

  const [result] = await db.query(
    `
    INSERT INTO player_profiles (
      account_id,
      nickname
    )
    VALUES (?, ?)
    `,
    [account_id, nickname]
  );

  return result.insertId;
}
export async function findProfileByAccountId(accountId, connection = null) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      profile_id,
      account_id,
      nickname,
      level,
      exp,
      created_at
    FROM player_profiles
    WHERE account_id = ?
    LIMIT 1
    `,
    [accountId]
  );

  return rows[0] || null;
}

export async function createInventory(profileId, connection = null) {
  const db = getExecutor(connection);

  const [result] = await db.query(
    `
    INSERT INTO inventories (
      profile_id
    )
    VALUES (?)
    `,
    [profileId]
  );

  return result.insertId;
}

export async function createDefaultCurrencies(profileId, connection = null) {
  const db = getExecutor(connection);

  await db.query(
    `
    INSERT INTO player_currencies (
      profile_id,
      currency_type,
      amount
    )
    VALUES
      (?, 'gold', 0),
      (?, 'diamond', 0),
      (?, 'stamina', 120)
    `,
    [profileId, profileId, profileId]
  );
}