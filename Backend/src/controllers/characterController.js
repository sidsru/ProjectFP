import {
  getOwnedCharacters,
  checkOwnedCharacter,
  addOwnedCharacter
} from "../services/characterService.js";


export async function getOwnedCharactersController(req, res) {
  try {
    const accountId = req.query.accountId;

    const ownedCharacters = await getOwnedCharacters(accountId);

    return res.json({
      success: true,
      ownedCharacters
    });
  } catch (error) {
    console.error("GET OWNED CHARACTERS ERROR:", error);

    return res.status(400).json({
      success: false,
      error: error.message
    });
  }
}

export async function checkOwnedCharacterController(req, res) {
  try {
    const accountId = req.query.accountId;
    const characterId = req.query.characterId;

    const owned = await checkOwnedCharacter(accountId, characterId);

    return res.json({
      success: true,
      owned
    });
  } catch (error) {
    console.error("CHECK OWNED CHARACTER ERROR:", error);

    return res.status(400).json({
      success: false,
      error: error.message
    });
  }
}

export async function addOwnedCharacterController(req, res) {
  try {
    const { accountId, character_code } = req.body;

    const result = await addOwnedCharacter(accountId, character_code);

    return res.json({
      success: true,
      message: result.alreadyOwned ? "ALREADY_OWNED" : "CHARACTER_ADDED"
    });
  } catch (error) {
    console.error("ADD OWNED CHARACTER ERROR:", error);

    return res.status(400).json({
      success: false,
      error: error.message
    });
  }
}