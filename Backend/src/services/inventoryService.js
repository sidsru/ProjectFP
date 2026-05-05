import pool from "../db.js";

import {
  findInventoryItemsByAccountId,
  findInventoryByAccountId,
  findItemDefByCode,
  findInventoryItemBySlot,
  insertInventoryItem
} from "../repositories/inventoryRepository.js";

export async function getInventoryByAccountId(accountId) {
  const rows = await findInventoryItemsByAccountId(accountId);

  return rows.map(row => ({
    slotIndex: row.slot_index,
    quantity: row.quantity,
    item: {
      itemDefId: row.item_def_id,
      itemCode: row.item_code,
      itemName: row.item_name,
      itemType: row.item_type,
      maxStack: row.max_stack
    }
  }));
}

export async function addItemByAccountId({
  accountId,
  itemCode,
  quantity,
  slotIndex
}) {
  const connection = await pool.getConnection();

  try {
    await connection.beginTransaction();

    const inventory = await findInventoryByAccountId(accountId, connection);

    if (!inventory) {
      throw new Error("INVENTORY_NOT_FOUND");
    }

    const itemDef = await findItemDefByCode(itemCode, connection);

    if (!itemDef) {
      throw new Error("ITEM_DEF_NOT_FOUND");
    }

    const existingSlotItem = await findInventoryItemBySlot(
      {
        inventoryId: inventory.inventory_id,
        slotIndex
      },
      connection
    );

    if (existingSlotItem) {
      throw new Error("SLOT_ALREADY_USED");
    }

    const inventoryItemId = await insertInventoryItem(
      {
        inventoryId: inventory.inventory_id,
        itemDefId: itemDef.item_def_id,
        quantity,
        slotIndex
      },
      connection
    );

    await connection.commit();

    return {
      inventoryItemId,
      inventoryId: inventory.inventory_id,
      itemDefId: itemDef.item_def_id,
      itemCode: itemDef.item_code,
      quantity,
      slotIndex
    };
  } catch (err) {
    await connection.rollback();
    throw err;
  } finally {
    connection.release();
  }
}