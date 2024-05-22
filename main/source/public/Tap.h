#pragma once

#include "Player.h"
#include "SimpleGameTypes.h"
#include <string>

class GameLoop;

class Tap
{
public:

    Tap(eGameSide _PlayerSide, std::string _AchievementKey, GameLoop* _GameLoop);
    std::string GetAchievementKey() { return achievementKey; }
    eGameSide GetPlayerSide() { return playerSide; }
    
private:

    std::string achievementKey;
    eGameSide playerSide;
};