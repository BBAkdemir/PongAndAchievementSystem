#include "public/Pong/Ball.h"
#include "public/DataContainer.h"
#include <SDL.h>
#include <iostream>

Ball::Ball(Vec2 position, Vec2 velocity)
	: position(position), velocity(velocity)
{
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = BALL_WIDTH;
	rect.h = BALL_HEIGHT;
}

// Calculates the ball's new position by multiplying their velocity by deltatime
void Ball::Update(float dt)
{
	position += velocity * dt;
}

// Draws the ball on the screen according to its position
void Ball::Draw(SDL_Renderer* renderer)
{
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}

// Calculates the change in velocity of the ball when it hits the player
void Ball::CollideWithPaddle(Contact const& contact)
{
	position.x += contact.penetration;
	velocity.x = -velocity.x;

	if (contact.type == CollisionType::Top)
	{
		velocity.y = -.75f * BALL_SPEED;
	}
	else if (contact.type == CollisionType::Bottom)
	{
		velocity.y = 0.75f * BALL_SPEED;
	}
}

// Calculates the change in velocity of the ball when it hits the Wall
void Ball::CollideWithWall(Contact const& contact)
{
	if ((contact.type == CollisionType::Top)
		|| (contact.type == CollisionType::Bottom))
	{
		position.y += contact.penetration;
		velocity.y = -velocity.y;
	}
	else if (contact.type == CollisionType::Left)
	{
		position.x = WINDOW_WIDTH / 2.0f;
		position.y = WINDOW_HEIGHT / 2.0f;
		velocity.x = BALL_SPEED;
		velocity.y = 0.75f * BALL_SPEED;
	}
	else if (contact.type == CollisionType::Right)
	{
		position.x = WINDOW_WIDTH / 2.0f;
		position.y = WINDOW_HEIGHT / 2.0f;
		velocity.x = -BALL_SPEED;
		velocity.y = 0.75f * BALL_SPEED;
	}
}

// Function that resets the ball to its initial values
void Ball::NewGame()
{
	position = Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	velocity = Vec2(BALL_SPEED, 0.0f);
}
