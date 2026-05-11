import mysql from "mysql2/promise";
import dotenv from "dotenv"; // .env를 인클루드

dotenv.config(); // .env 파일을 읽어옴

const pool = mysql.createPool({
  host: process.env.DB_HOST, // .env 파일에 있는 DB_HOST를 읽어옴
  port: Number(process.env.DB_PORT || 3306), // .env 파일에 있는 DB_PORT를 읽어옴
  user: process.env.DB_USER, // .env 파일에 있는 DB_USER를 읽어옴
  password: process.env.DB_PASSWORD, // .env 파일에 있는 DB_PASSWORD를 읽어옴
  database: process.env.DB_NAME, // .env 파일에 있는 DB_NAME를 읽어옴
});

export default pool; // pool을 내보냄