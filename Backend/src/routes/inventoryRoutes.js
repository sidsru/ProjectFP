import express from "express";
import { authMiddleware } from "../middlewares/authMiddleware.js";

import {
  getMyInventory,
  addItemToMyInventory
} from "../controllers/inventoryController.js";

const router = express.Router();

router.get("/", authMiddleware, getMyInventory);

// 테스트용 API.
// 실제 게임에서는 클라이언트가 마음대로 아이템 추가 요청을 보내면 안 된다.
// 퀘스트 보상, 상점 구매, 전투 보상 같은 서버 로직 안에서 호출하는 구조가 안전하다.
router.post("/add", authMiddleware, addItemToMyInventory);

export default router;