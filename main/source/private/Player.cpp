#include "public/Player.h"
#include "public/DataContainer.h"
#include "public/Pong/ScoreUIElement.h"

#include <SDL.h>

Player::Player(eGameSide _PlayerSide, Vec2 _position, Vec2 _velocity) : position(_position), velocity(_velocity)
{
	rect.x = static_cast<int>(_position.x);
	rect.y = static_cast<int>(_position.y);
	rect.w = PADDLE_WIDTH;
	rect.h = PADDLE_HEIGHT;

	data = std::make_unique<PlayerDataHandler>(_PlayerSide, 0, 0, 0);
}

Player::~Player()
{
}

// Calculates the player's new position by multiplying their velocity by deltatime
void Player::Update(float dt)
{
	position += velocity * dt;

	if (position.y < 0)
	{
		// Restrict to top of the screen
		position.y = 0;
	}
	else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT))
	{
		// Restrict to bottom of the screen
		position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
	}
}

// Draws the player on the screen according to its position
void Player::Draw(SDL_Renderer* renderer)
{
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}

// It calculates the speed value according to the "KeyEvents" returned from the "InputManager".
void Player::PlayerInput(bool _ButtonUp, bool _ButtonDown)
{
	if (_ButtonUp)
	{
		velocity.y = -PADDLE_SPEED;
	}
	else if (_ButtonDown)
	{
		velocity.y = PADDLE_SPEED;
	}
	else
	{
		velocity.y = 0.0f;
	}
}

// Function that resets the player to its initial values
void Player::NewGame()
{
	data->SetScore(0);
	//Achievements.clear();
	if (data->GetPlayerSide() == eGameSide::PLAYER)
		position = Vec2(50.0f, WINDOW_HEIGHT / 2.0f);
	else
		position = Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f);
}

// Adds rewards from the "_Rewards" list to the player according to their type
void Player::AddRewards(std::vector<std::unique_ptr<sReward>>& _Rewards)
{
	for (int i = 0; i < _Rewards.size(); i++)
	{
		data->SetCurrency(_Rewards[i]->CurrencyAmount, _Rewards[i]->CurrencyType);
	}
}
