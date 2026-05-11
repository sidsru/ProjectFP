import express from "express";
import {
  register,
  login
} from "../controllers/authController.js"; // 해당 파일에 있는 함수를 가져옴

const router = express.Router(); // express.Router를 사용하여 라우터를 생성

router.post("/register", register); // 회원가입 라우터 함수 호출
router.post("/login", login); // 로그인 라우터 함수 호출

export default router;