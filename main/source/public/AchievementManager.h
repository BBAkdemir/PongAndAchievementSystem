#pragma once

#include <string>
#include "DataContainer.h"
#include "Player.h"

class GameLoop;

class AchievementManager
{
public:

	AchievementManager(std::shared_ptr<DataContainer> _dataContainer, GameLoop* _GameLoop);
	~AchievementManager();

	// It allows a player's achievement or achievement progress value to be increased and given to the player.
	void SetAchievementProgress(std::string _AchievementKey, int _AddedProgressCount, std::unique_ptr<Player>& _AffectPlayer);
	// Function that creates a new achievement, increases the progress value by the entered value, and then adds it to the player.
	void CreateAndAddAchievementProgress(std::string _AchievementKey, int _AddedProgressCount, std::unique_ptr<Player>& _AffectPlayer);

private:

	std::shared_ptr<DataContainer> dataContainer;
	GameLoop* gameLoop;
};

