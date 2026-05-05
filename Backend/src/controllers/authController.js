import {
    registerAccount,
    loginAccount
  } from "../services/authService.js";
  
  export async function register(req, res) {
    try {
      const { UserID, password, nickname } = req.body;
  
      if (!UserID || !password) {
        return res.status(400).json({
          success: false,
          error: "UserID_AND_PASSWORD_REQUIRED"
        });
      }
  
      const result = await registerAccount({
        UserID,
        password,
        nickname
      });
  
      return res.status(201).json({
        success: true,
        accessToken: result.accessToken,
        account: result.account,
        profile: result.profile
      });
    } catch (err) {
      console.error(err);
  
      if (err.message === "DUPLICATED_USER_ID") {
        return res.status(409).json({
          success: false,
          error: "DUPLICATED_USER_ID"
        });
      }
  
      return res.status(500).json({
        success: false,
        error: "SERVER_ERROR"
      });
    }
  }
  
  export async function login(req, res) {
    try {
      const { UserID, password } = req.body;
  
      if (!UserID || !password) {
        return res.status(400).json({
          success: false,
          error: "UserID_AND_PASSWORD_REQUIRED"
        });
      }
  
      const result = await loginAccount({
        UserID,
        password
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