import pool from "../db.js";

function getExecutor(connection) {
  return connection || pool;
}

export async function findInventoryByAccountId(accountId, connection = null) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      inv.inventory_id,
      inv.profile_id
    FROM accounts a
    JOIN player_profiles pp
      ON pp.account_id = a.account_id
    JOIN inventories inv
      ON inv.profile_id = pp.profile_id
    WHERE a.account_id = ?
    LIMIT 1
    `,
    [accountId]
  );

  return rows[0] || null;
}

export async function findInventoryItemsByAccountId(
  accountId,
  connection = null
) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      ii.inventory_item_id,
      ii.inventory_id,
      ii.item_def_id,
      ii.quantity,
      ii.slot_index,
      idf.item_code,
      idf.item_name,
      idf.item_type,
      idf.max_stack
    FROM accounts a
    JOIN player_profiles pp
      ON pp.account_id = a.account_id
    JOIN inventories inv
      ON inv.profile_id = pp.profile_id
    JOIN inventory_items ii
      ON ii.inventory_id = inv.inventory_id
    JOIN item_defs idf
      ON idf.item_def_id = ii.item_def_id
    WHERE a.account_id = ?
    ORDER BY ii.slot_index ASC
    `,
    [accountId]
  );

  return rows;
}

export async function findItemDefByCode(itemCode, connection = null) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      item_def_id,
      item_code,
      item_name,
      item_type,
      max_stack
    FROM item_defs
    WHERE item_code = ?
    LIMIT 1
    `,
    [itemCode]
  );

  return rows[0] || null;
}

export async function findInventoryItemBySlot(
  {
    inventoryId,
    slotIndex
  },
  connection = null
) {
  const db = getExecutor(connection);

  const [rows] = await db.query(
    `
    SELECT
      inventory_item_id,
      inventory_id,
      item_def_id,
      quantity,
      slot_index
    FROM inventory_items
    WHERE inventory_id = ?
      AND slot_index = ?
    LIMIT 1
    `,
    [inventoryId, slotIndex]
  );

  return rows[0] || null;
}

export async function insertInventoryItem(
  {
    inventoryId,
    itemDefId,
    quantity,
    slotIndex
  },
  connection = null
) {
  const db = getExecutor(connection);

  const [result] = await db.query(
    `
    INSERT INTO inventory_items (
      inventory_id,
      item_def_id,
      quantity,
      slot_index
    )
    VALUES (?, ?, ?, ?)
    `,
    [inventoryId, itemDefId, quantity, slotIndex]
  );

  return result.insertId;
}