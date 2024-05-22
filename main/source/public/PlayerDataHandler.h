#pragma once

#include "SimpleGameTypes.h"

class PlayerDataHandler
{
private:

	eGameSide playerSide;
	int score;
	int gold;
	int diamond;

public:

	PlayerDataHandler() : playerSide(eGameSide::PLAYER), score(0), gold(0), diamond(0) {}
	PlayerDataHandler(eGameSide _PlayerSide, int _Score, int _Gold, int _Diamond) : playerSide(_PlayerSide), score(_Score), gold(_Gold), diamond(_Diamond) {}

	eGameSide GetPlayerSide() { return playerSide; }

	void ScoreIncrease() { score++; }
	int GetScore() { return score; }

	void SetScore(const int amount)
	{
		score = amount;
	}

	int GetGold() { return gold; }
	int GetDiamond() { return diamond; }
	 
	// It is used for updating a dedicated hard currency owned by the player
	void SetCurrency(const int amount, const eCurrencyType type)
	{
		if (type == eCurrencyType::GOLD)
		{
			gold += amount;
		}
		else
		{
			diamond += amount;
		}
	}
};