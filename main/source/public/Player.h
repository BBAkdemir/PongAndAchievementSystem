#pragma once

#include <iostream>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "public/Pong/Vec2.h"
#include <vector>
#include "AchievementDefinition.h"
#include "PlayerDataHandler.h"

enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};

struct sAchievement
{
	std::string AchievementKey = "";
	int ProgressCount = 0;
	int WinCondition = 1;
	bool bIsAchieved = false;
};

class Player
{
public:

	Player(eGameSide _PlayerSide, Vec2 _position, Vec2 _velocity);
	~Player();

	// Calculates the player's new position by multiplying their velocity by deltatime
	void Update(float dt);
	// Draws the player on the screen according to its position
	void Draw(SDL_Renderer* renderer);
	// It calculates the speed value according to the "KeyEvents" returned from the "InputManager".
	void PlayerInput(bool _ButtonUp, bool _ButtonDown);
	// Function that resets the player to its initial values
	void NewGame();

	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};

	// Adds rewards from the "_Rewards" list to the player according to their type
	void AddRewards(std::vector<std::unique_ptr<sReward>>& _Rewards);
	// Returns player's achievements
	std::vector<std::unique_ptr<sAchievement>>& GetAchievements() { return achievements; }
	// Returns player's side, score and currency value.
	std::unique_ptr<PlayerDataHandler>& GetData() { return data; }

protected:

	std::vector<std::unique_ptr<sAchievement>> achievements;
	std::unique_ptr<PlayerDataHandler> data;
};

