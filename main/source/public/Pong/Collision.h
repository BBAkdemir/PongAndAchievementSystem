#pragma once

#include <SDL_mixer.h>
#include "public/Pong/Vec2.h"
#include <iostream>

class Ball;
class Player;
class GameLoop;

class Collision
{
public:

	// function that calculates how the ball will behave in the event of collisions with the player.
	Contact CheckPlayerCollision(std::unique_ptr<Ball>& _Ball, std::unique_ptr<Player>& _Player);
	// function that calculates how the ball will behave in the event of collisions with walls
	Contact CheckWallCollision(std::unique_ptr<Ball>& _Ball);
	// function where all collision situations are calculated and what behavior will occur in the face of them.
	void CheckAllCollision(std::unique_ptr<Ball>& _Ball, std::unique_ptr<Player>& _PlayerOne, std::unique_ptr<Player>& _PlayerTwo, Mix_Chunk* _WallHitSound, Mix_Chunk* _PaddleHitSound, GameLoop& _GameLoop);
};