import pool from "../db.js";

export async function findOwnedCharactersByAccountId(accountId) {
  const [rows] = await pool.query(
    `
    SELECT
      owned_character_id,
      account_id,
      character_id,
      created_at
    FROM owned_characters
    WHERE account_id = ?
    ORDER BY owned_character_id ASC
    `,
    [accountId]
  );

  return rows;
}

export async function existsOwnedCharacter(accountId, 	character_id) {
  const [rows] = await pool.query(
    `
    SELECT 1
    FROM owned_characters
    WHERE account_id = ?
      AND character_id = ?
    LIMIT 1
    `,
    [accountId, String(	character_id)]
  );

  return rows.length > 0;
}

export async function insertOwnedCharacter(accountId, character_id) {
  const [result] = await pool.query(
    `
    INSERT INTO owned_characters (
      account_id,
      character_id
    )
    VALUES (?, ?)
    `,
    [accountId, character_id]
  );

  return {
    owned_character_id: result.insertId,
    account_id: accountId,
    character_id: character_id
  };
}