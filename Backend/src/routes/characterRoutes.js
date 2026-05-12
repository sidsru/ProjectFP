import express from "express";

import {
  getOwnedCharactersController,
  checkOwnedCharacterController,
  addOwnedCharacterController
} from "../controllers/characterController.js";

const router = express.Router();

router.get("/owned", getOwnedCharactersController);

router.get("/owned/check", checkOwnedCharacterController);

router.post("/owned", addOwnedCharacterController);

export default router;