import {
    registerAccount,
    loginAccount
  } from "../services/authService.js";
  
  export async function register(req, res) {
    try {
      const { UserID, Password } = req.body;
  
      if (!UserID || !Password) {
        return res.status(400).json({
          success: false,
          error: "UserID_AND_PASSWORD_REQUIRED"
        });
      }
  
      const result = await registerAccount({
        UserID, // 유저 아이디
        Password // 비밀번호
      });//회원 가입 시도

      // 회원 가입 성공 시 응답
      return res.status(201).json({
        success: true,
        accessToken: result.accessToken,
        account: result.account,
        profile: result.profile
      });
    } catch (err) {
      console.error("REGISTER ERROR:", err);
  
      // 중복 아이디 처리
      if (err.message === "DUPLICATED_USER_ID") {
        return res.status(409).json({
          success: false,
          error: "DUPLICATED_USER_ID"
        });
      }
  
      // 외 다른 모든 오류 처리
      return res.status(500).json({
        success: false,
        error: "SERVER_ERROR",
        detail: err.message
      });
    }
  }
  
  export async function login(req, res) {
    try {
      const { UserID, Password } = req.body;
  
      if (!UserID || !Password) {
        return res.status(400).json({
          success: false,
          error: "UserID_AND_PASSWORD_REQUIRED"
        });
      }
  
      const result = await loginAccount({
        UserID,
        Password
      });
  
      return res.json({
        success: true,
        accessToken: result.accessToken,
        account: result.account,
        profile: result.profile
      });
    } catch (err) {
      console.error(err);
  
      if (err.message === "INVALID_LOGIN") {
        return res.status(401).json({
          success: false,
          error: "INVALID_LOGIN"
        });
      }
  
      if (err.message === "ACCOUNT_BLOCKED") {
        return res.status(403).json({
          success: false,
          error: "ACCOUNT_BLOCKED"
        });
      }
  
      return res.status(500).json({
        success: false,
        error: "SERVER_ERROR"
      });
    }
  }