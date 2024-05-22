#pragma once

#include <vector>
#include <iostream>
#include "public/AchievementDefinition.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float PADDLE_SPEED = 1.0f;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const float BALL_SPEED = 1.0f;
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;
const int WIN_CONDITION = 10;// The amount of points a side must make to win the game.

// A dedicated data-container class holding all the required game data
class DataContainer
{
public:

    // This is where Achievement data is created.
    DataContainer();

    // Returns a list of AchievementDefinition instances
    const std::vector<std::unique_ptr<AchievementDefinition>>& GetAchievementDefinitions();

private:

    // list of AchievementDefinition
    std::vector<std::unique_ptr<AchievementDefinition>> achievementDefs;
};

