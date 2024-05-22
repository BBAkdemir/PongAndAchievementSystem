#include "Tap.h"

#include <iostream>
#include "AchievementManager.h"
#include "public/GameLoop.h"

Tap::Tap(eGameSide _PlayerSide, std::string _AchievementKey, GameLoop* _GameLoop) : playerSide(_PlayerSide), achievementKey(_AchievementKey)
{
	_GameLoop->OnTap(*this);
}
