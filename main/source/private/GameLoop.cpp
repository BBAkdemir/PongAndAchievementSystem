#include "public/GameLoop.h"

#include <chrono>
#include "public/Pong/Vec2.h"

#include "SDL.h"

// Triggers some related code to get and set the game data
// Creates the class that contains all game data
void GameLoop::ReceiveData()
{
	dataContainer = std::make_shared<DataContainer>();
}

// It creates the scene and all objects that will be rendered in the scene.
// Creates the achievement manager, the class that controls achievements
// Creates input manager, which is the class that helps us receive our button events.
void GameLoop::Start()
{
	std::cout << "Start The Game\n";

	// Create the Achievement Controller
	achievementManager = std::make_unique<AchievementManager>(dataContainer, this);
	// Create the Scene
	scene = std::make_shared<Scene>();
	// Create the ball
	ball = std::make_unique<Ball>(Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), Vec2(BALL_SPEED, 0.0f));
	// Create the Collision
	collision = std::make_unique<Collision>();
	// Create the Players
	playerOne = std::make_unique<Player>(eGameSide::PLAYER, Vec2(50.0f, WINDOW_HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
	playerTwo = std::make_unique<Player>(eGameSide::OPPONENT, Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
	// Create the ScoreTexts
	playerOneScoreText = std::make_unique<ScoreUIElement>(Vec2(WINDOW_WIDTH / 2 - 60, 20), scene.get());
	playerTwoScoreText = std::make_unique<ScoreUIElement>(Vec2(WINDOW_WIDTH / 2 + 30, 20), scene.get());
	// Create the Reward UIs
	playerOneGoldUI = std::make_unique<RewardUIElement>(Vec2(0, 20), scene.get(), "resources/images/Gold.bmp");
	playerOneDiamondUI = std::make_unique<RewardUIElement>(Vec2(150, 20), scene.get(), "resources/images/Diamond.bmp");
	playerTwoGoldUI = std::make_unique<RewardUIElement>(Vec2(WINDOW_WIDTH - 250, 20), scene.get(), "resources/images/Gold.bmp");
	playerTwoDiamondUI = std::make_unique<RewardUIElement>(Vec2(WINDOW_WIDTH - 100, 20), scene.get(), "resources/images/Diamond.bmp");
	// Create the Input Manager
	inputManager = std::make_unique<InputManager>();
}

void GameLoop::Run()
{
	running = true;
	dt = 0.0f;
	while (running)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		// Runs the function that returns which keys the players pressed
		inputManager->KeyControl(running, buttonOneUp, buttonOneDown, buttonTwoUp, buttonTwoDown);

		// It sends the key events returned from the input manager to the player classes and calculates the velocity value.
		playerOne->PlayerInput(buttonOneUp, buttonOneDown);
		playerTwo->PlayerInput(buttonTwoUp, buttonTwoDown);

		// Update the player positions
		playerOne->Update(dt);
		playerTwo->Update(dt);

		// Update the ball position
		ball->Update(dt);

		// Function that sends objects to the collision class, which is the class that manages collision operations, and calculates how they will behave in case of collision.
		collision->CheckAllCollision(ball, playerOne, playerTwo, scene->GetWallHitSound(), scene->GetPaddleHitSound(), *this);

		// Render All Objects
		scene->Render(ball, playerOne, playerTwo, playerOneScoreText, playerTwoScoreText, playerOneGoldUI, playerOneDiamondUI, playerTwoGoldUI, playerTwoDiamondUI, dt);

		// Calculate frame time
		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}

	// destroy scene
	scene->Destroy();
}

// A method called when a tapping event happens
void GameLoop::OnTap(Tap& tap)
{
	// Tap achievements are progressed here.
	if (tap.GetPlayerSide() == eGameSide::PLAYER)
		achievementManager->SetAchievementProgress(tap.GetAchievementKey(), 1, playerOne);
	else
		achievementManager->SetAchievementProgress(tap.GetAchievementKey(), 1, playerTwo);
}

// A method called when one of the sides scores a goal, the score parameter keeps the character's current score, the egameside parameter keeps which side scored.
void GameLoop::OnScore(const int score, const eGameSide _GetPlayer)
{
	// Score is added for each player and the "First score" achievement is triggered.
	if (_GetPlayer == eGameSide::PLAYER)
	{
		// Sends the player's score to update it to the relevant text parameter
		playerOneScoreText->SetScore(score);
		if (score == 1)
		{
			// "First score" achievement progress section.
			achievementManager->SetAchievementProgress("Ach3", 1, playerOne);
		}
	}
	else
	{
		playerTwoScoreText->SetScore(score);
		if (score == 1)
		{
			achievementManager->SetAchievementProgress("Ach3", 1, playerTwo);
		}	
	}	
}

// A method called when the game session finishes.eGameSide parameter holds the side winning the session.
void GameLoop::OnMatchResult(const eGameSide _WinPlayer)
{
	// The "First win" achievement is triggered for the winning player.
	if (_WinPlayer == eGameSide::PLAYER)
		achievementManager->SetAchievementProgress("Ach4", 1, playerOne);
	else
		achievementManager->SetAchievementProgress("Ach4", 1, playerTwo);

	// Here the objects in the scene are reset
	playerOne->NewGame();
	playerTwo->NewGame();
	ball->NewGame();
	playerOneScoreText->SetScore(0);
	playerTwoScoreText->SetScore(0);
}

// This updates the value of players reward UIs. The "sReward" list holds data for the rewards to be added. "eGameSide" parameter determines which player's reward UI will be updated.
void GameLoop::SetRewardChangedUI(std::vector<std::unique_ptr<sReward>>& _Rewards, eGameSide _RewardPlayer)
{
	if (_RewardPlayer == eGameSide::PLAYER)
	{
		for (int i = 0; i < _Rewards.size(); i++)
		{
			if (_Rewards[i]->CurrencyType == eCurrencyType::GOLD)
			{
				playerOneGoldUI->SetCount(playerOne->GetData()->GetGold() + _Rewards[i]->CurrencyAmount);
			}
			else
			{
				playerOneDiamondUI->SetCount(playerOne->GetData()->GetDiamond() + _Rewards[i]->CurrencyAmount);
			}
		}
	}
	else
	{
		for (int i = 0; i < _Rewards.size(); i++)
		{
			if (_Rewards[i]->CurrencyType == eCurrencyType::GOLD)
			{
				playerTwoGoldUI->SetCount(playerTwo->GetData()->GetGold() + _Rewards[i]->CurrencyAmount);
			}
			else
			{
				playerTwoDiamondUI->SetCount(playerTwo->GetData()->GetDiamond() + _Rewards[i]->CurrencyAmount);
			}
		}
	}
}
