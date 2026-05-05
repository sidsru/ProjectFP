import {
    getInventoryByAccountId,
    addItemByAccountId
  } from "../services/inventoryService.js";
  
  export async function getMyInventory(req, res) {
    try {
      const accountId = req.user.accountId;
  
      const inventory = await getInventoryByAccountId(accountId);
  
      return res.json({
        success: true,
        inventory
      });
    } catch (err) {
      console.error(err);
  
      return res.status(500).json({
        success: false,
        error: "SERVER_ERROR"
      });
    }
  }
  
  export async function addItemToMyInventory(req, res) {
    try {
      const accountId = req.user.accountId;
      const { itemCode, quantity, slotIndex } = req.body;
  
      if (!itemCode || quantity == null || slotIndex == null) {
        return res.status(400).json({
          success: false,
          error: "itemCode_quantity_slotIndex_REQUIRED"
        });
      }
  
      const result = await addItemByAccountId({
        accountId,
        itemCode,
        quantity,
        slotIndex
      });
  
      return res.json({
        success: true,
        result
      });
    } catch (err) {
      console.error(err);
  
      if (err.message === "ITEM_DEF_NOT_FOUND") {
        return res.status(404).json({
          success: false,
          error: "ITEM_DEF_NOT_FOUND"
        });
      }
  
      if (err.message === "SLOT_ALREADY_USED") {
        return res.status(409).json({
          success: false,
          error: "SLOT_ALREADY_USED"
        });
      }
  
      return res.status(500).json({
        success: false,
        error: "SERVER_ERROR"
      });
    }
  }