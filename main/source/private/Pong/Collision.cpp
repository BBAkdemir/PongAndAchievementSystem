#include "public/Pong/Collision.h"
#include "public/DataContainer.h"
#include "public/Tap.h"
#include "public/Pong/Ball.h"
#include "public/Player.h"
#include "public/AchievementManager.h"
#include "public/Scene.h"
#include "public/GameLoop.h"
#include "public/SimpleGameTypes.h"

// function that calculates how the ball will behave in the event of collisions with the player.
Contact Collision::CheckPlayerCollision(std::unique_ptr<Ball>& _Ball, std::unique_ptr<Player>& _Player)
{
	float ballLeft = _Ball->position.x;
	float ballRight = _Ball->position.x + BALL_WIDTH;
	float ballTop = _Ball->position.y;
	float ballBottom = _Ball->position.y + BALL_HEIGHT;

	float playerLeft = _Player->position.x;
	float playerRight = _Player->position.x + PADDLE_WIDTH;
	float playerTop = _Player->position.y;
	float playerBottom = _Player->position.y + PADDLE_HEIGHT;

	Contact contact{};

	if (ballLeft >= playerRight)
	{
		return contact;
	}

	if (ballRight <= playerLeft)
	{
		return contact;
	}

	if (ballTop >= playerBottom)
	{
		return contact;
	}

	if (ballBottom <= playerTop)
	{
		return contact;
	}

	float playerRangeUpper = playerBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
	float playerRangeMiddle = playerBottom - (PADDLE_HEIGHT / 3.0f);

	if (_Ball->velocity.x < 0)
	{
		// Left paddle
		contact.penetration = playerRight - ballLeft;
	}
	else if (_Ball->velocity.x > 0)
	{
		// Right paddle
		contact.penetration = playerLeft - ballRight;
	}

	if ((ballBottom > playerTop)
		&& (ballBottom < playerRangeUpper))
	{
		contact.type = CollisionType::Top;
	}
	else if ((ballBottom > playerRangeUpper)
		&& (ballBottom < playerRangeMiddle))
	{
		contact.type = CollisionType::Middle;
	}
	else
	{
		contact.type = CollisionType::Bottom;
	}

	return contact;
}

// function that calculates how the ball will behave in the event of collisions with walls
Contact Collision::CheckWallCollision(std::unique_ptr<Ball>& _Ball)
{
	float ballLeft = _Ball->position.x;
	float ballRight = _Ball->position.x + BALL_WIDTH;
	float ballTop = _Ball->position.y;
	float ballBottom = _Ball->position.y + BALL_HEIGHT;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
	}
	else if (ballRight > WINDOW_WIDTH)
	{
		contact.type = CollisionType::Right;
	}
	else if (ballTop < 0.0f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > WINDOW_HEIGHT)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = WINDOW_HEIGHT - ballBottom;
	}

	return contact;
}

// function where all collision situations are calculated and what behavior will occur in the face of them.
void Collision::CheckAllCollision(std::unique_ptr<Ball>& _Ball, std::unique_ptr<Player>& _PlayerOne, std::unique_ptr<Player>& _PlayerTwo, Mix_Chunk* _WallHitSound, Mix_Chunk* _PaddleHitSound, GameLoop& _GameLoop)
{
	if (Contact contact = CheckPlayerCollision(_Ball, _PlayerOne); contact.type != CollisionType::None)
	{
		_Ball->CollideWithPaddle(contact);
		// In case the ball hits the player, we create a new tap class and take the necessary actions within it.
		Tap NewTap(eGameSide::PLAYER, "Ach1", &_GameLoop);
		Tap NewTap2(eGameSide::PLAYER, "Ach2", &_GameLoop);
		// We play sound if the ball hits the player
		Mix_PlayChannel(-1, _PaddleHitSound, 0);
	}
	else if (contact = CheckPlayerCollision(_Ball, _PlayerTwo); contact.type != CollisionType::None)
	{
		_Ball->CollideWithPaddle(contact);
		// In case the ball hits the player, we create a new tap class and take the necessary actions within it.
		Tap NewTap(eGameSide::OPPONENT, "Ach1", &_GameLoop);
		Tap NewTap2(eGameSide::OPPONENT, "Ach2", &_GameLoop);
		// We play sound if the ball hits the player
		Mix_PlayChannel(-1, _PaddleHitSound, 0);
	}
	else if (contact = CheckWallCollision(_Ball); contact.type != CollisionType::None)
	{
		_Ball->CollideWithWall(contact);

		if (contact.type == CollisionType::Left)
		{
			// If the ball hits the left wall, we increase the score of "playerTwo" and call the score function in our gameloop class.
			// If our score is higher than the winning condition of the game, we become the winner of the game and the onmatchresult function in the game loop class is run.
			_PlayerTwo->GetData()->ScoreIncrease();
			_GameLoop.OnScore(_PlayerTwo->GetData()->GetScore(), eGameSide::OPPONENT);
			if (_PlayerTwo->GetData()->GetScore() == WIN_CONDITION)
				_GameLoop.OnMatchResult(eGameSide::OPPONENT);
		}
		else if (contact.type == CollisionType::Right)
		{
			// If the ball hits the right wall, we increase the score of "playerOne" and call the score function in our gameloop class.
			// If our score is higher than the winning condition of the game, we become the winner of the game and the onmatchresult function in the game loop class is run.
			_PlayerOne->GetData()->ScoreIncrease();
			_GameLoop.OnScore(_PlayerOne->GetData()->GetScore(), eGameSide::PLAYER);
			if (_PlayerOne->GetData()->GetScore() == WIN_CONDITION)
				_GameLoop.OnMatchResult(eGameSide::PLAYER);
		}
		else
		{
			//We play sound if the ball hits the upper and lower wall
			Mix_PlayChannel(-1, _WallHitSound, 0);
		}
	}
}
