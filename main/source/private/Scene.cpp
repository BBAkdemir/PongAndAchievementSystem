#include "public/Scene.h"
#include "public/DataContainer.h"
#include "public/Pong/Ball.h"
#include "public/Player.h"
#include "public/Pong/ScoreUIElement.h"
#include "public/Pong/Vec2.h"

Scene::Scene()
{
	// Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	// Initialize the font
	scoreFont = TTF_OpenFont("resources/fonts/DejaVuSansMono.ttf", 40);

	// Initialize sound effects
	wallHitSound = Mix_LoadWAV("resources/sounds/WallHit.wav");
	paddleHitSound = Mix_LoadWAV("resources/sounds/PaddleHit.wav");
}

// The function where all objects in the game are rendered.
void Scene::Render(unique_ptr<Ball>& _ball, unique_ptr<Player>& _playerOne, unique_ptr<Player>& _PlayerTwo,
	unique_ptr<ScoreUIElement>& _PlayerOneScoreText, unique_ptr<ScoreUIElement>& _PlayerTwoScoreText,
	unique_ptr<RewardUIElement>& _PlayerOneGoldUI, unique_ptr<RewardUIElement>& _PlayerOneDiamondUI,
	unique_ptr<RewardUIElement>& _PlayerTwoGoldUI, unique_ptr<RewardUIElement>& _PlayerTwoDiamondUI,
	float dt)
{
	// Clear the window to black
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);

	// Set the draw color to be white
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Draw the net
	for (int y = 0; y < WINDOW_HEIGHT; ++y)
		if (y % 5)
			SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);

	// Draw the ball
	_ball->Draw(renderer);

	// Draw the paddles
	_playerOne->Draw(renderer);
	_PlayerTwo->Draw(renderer);

	// Display the scores
	_PlayerOneScoreText->Draw();
	_PlayerTwoScoreText->Draw();

	// Display the Rewards
	_PlayerOneGoldUI->Draw();
	_PlayerOneDiamondUI->Draw();
	_PlayerTwoGoldUI->Draw();
	_PlayerTwoDiamondUI->Draw();

	bool bIsDelete = false;
	int index = -1;
	if (Achievements.size() > 0)
		for (int i = 0; i < Achievements.size(); i++)
		{
			// This was done to limit errors that may occur if the number is too large.
			if (dt > 0.001f)
				dt = 0.001f;
			bool tmpDel = Achievements[i]->Draw(dt);
			if (tmpDel)
			{
				bIsDelete = true;
			}
		}
	if (bIsDelete)
	{
		Remove(*Achievements.begin());
	}
	// Present the backbuffer
	SDL_RenderPresent(renderer);
}

// Destroy all SDL class
void Scene::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreFont);
	Mix_FreeChunk(wallHitSound);
	Mix_FreeChunk(paddleHitSound);
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

// Adds the given UIElement to the UI.A UIElement added by Scene::Add() stays on the UI until it is removed via Scene::Remove()
void Scene::Add(std::unique_ptr<UIElement>& elem)
{
	Achievements.push_back(std::move(elem));
}

// Removes the given UIElement from the UI. A UIElement added by Scene::Add() stays on the UI until it is removed via Scene::Remove()
void Scene::Remove(std::unique_ptr<UIElement>& elem)
{
	auto it = std::find(Achievements.begin(), Achievements.end(), elem);
	int index = std::distance(Achievements.begin(), it);
	Achievements.erase(Achievements.begin() + index);
}
