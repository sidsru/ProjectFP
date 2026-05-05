import jwt from "jsonwebtoken";

export function authMiddleware(req, res, next) {
  const authHeader = req.headers.authorization;

  if (!authHeader) {
    return res.status(401).json({
      success: false,
      error: "NO_AUTHORIZATION_HEADER"
    });
  }

  if (!authHeader.startsWith("Bearer ")) {
    return res.status(401).json({
      success: false,
      error: "INVALID_AUTHORIZATION_FORMAT"
    });
  }

  const token = authHeader.replace("Bearer ", "");

  try {
    const decoded = jwt.verify(token, process.env.JWT_SECRET);

    req.user = {
      accountId: decoded.accountId,
      userId: decoded.userId
    };

    next();
  } catch (err) {
    return res.status(401).json({
      success: false,
      error: "INVALID_OR_EXPIRED_TOKEN"
    });
  }
}