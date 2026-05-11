import express from "express";
import cors from "cors";
import dotenv from "dotenv";

import authRoutes from "./routes/authRoutes.js";
import inventoryRoutes from "./routes/inventoryRoutes.js";

dotenv.config();

const app = express();

app.use(cors());
app.use(express.json());

// 기본 라우터 호출 메시지 
app.get("/", (req, res) => {
  res.json({
    success: true,
    message: "ProjectFP Backend Server"
  });
});

// 인증 라우터 호출
app.use("/auth", authRoutes);

// 인벤토리 라우터 호출
app.use("/inventory", inventoryRoutes);

const PORT = process.env.PORT || 3000;

// 서버 실행
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});