import {
  findOwnedCharactersByAccountId,
  existsOwnedCharacter,
  insertOwnedCharacter
} from "../repositories/characterRepository.js";

export async function getOwnedCharacters(accountId) {
  if (!accountId) {
    throw new Error("MISSING_ACCOUNT_ID");
  }

  return await findOwnedCharactersByAccountId(accountId);
}

export async function checkOwnedCharacter(accountId, characterId) {
  if (!accountId || !characterId) {
    throw new Error("MISSING_FIELDS");
  }

  return await existsOwnedCharacter(accountId, characterId);
}

export async function addOwnedCharacter(accountId, character_code) {
  if (!accountId || !character_code) {
    throw new Error("MISSING_FIELDS");
  }

  const alreadyOwned = await existsOwnedCharacter(accountId, character_code);

  if (alreadyOwned) {
    return {
      alreadyOwned: true
    };
  }

  await insertOwnedCharacter(accountId, character_code);

  return {
    alreadyOwned: false
  };
}