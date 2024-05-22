#pragma once

#include "SDL_render.h"
#include "SDL_rect.h"
#include "Vec2.h"

class Vec2;

class Ball
{
public:

	Ball(Vec2 _position, Vec2 _velocity);
	// Calculates the ball's new position by multiplying their velocity by deltatime
	void Update(float dt);
	// Draws the ball on the screen according to its position
	void Draw(SDL_Renderer* renderer);
	// Calculates the change in velocity of the ball when it hits the player
	void CollideWithPaddle(Contact const& contact);
	// Calculates the change in velocity of the ball when it hits the Wall
	void CollideWithWall(Contact const& contact);

	// Function that resets the ball to its initial values
	void NewGame();

	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};
};

