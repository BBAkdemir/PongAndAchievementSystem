#pragma once
#include "SDL_video.h"
#include "SDL_mixer.h"
#include <iostream>
#include <memory.h>
#include "public/Pong/ScoreUIElement.h"
#include "RewardUIElement.h"
#include "UIElement.h"
#include <vector>

using std::shared_ptr;
using std::unique_ptr;
using std::vector;

class Ball;
class Player;

class Scene
{
public:

    Scene();

    // The function where all objects in the game are rendered.
    void Render(unique_ptr<Ball>& _ball, unique_ptr<Player>& _playerOne, unique_ptr<Player>& _PlayerTwo,
        unique_ptr<ScoreUIElement>& _PlayerOneScoreText, unique_ptr<ScoreUIElement>& _PlayerTwoScoreText,
        unique_ptr<RewardUIElement>& _PlayerOneGoldUI, unique_ptr<RewardUIElement>& _PlayerOneDiamondUI,
        unique_ptr<RewardUIElement>& _PlayerTwoGoldUI, unique_ptr<RewardUIElement>& _PlayerTwoDiamondUI,
        float dt);

    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* scoreFont;

    Mix_Chunk* wallHitSound;
    Mix_Chunk* paddleHitSound;

    void Destroy();

    //A UIElement added by Scene::Add() stays on the UI
    // until it is removed via Scene::Remove()
    void Add(unique_ptr<UIElement>& elem);
    void Remove(unique_ptr<UIElement>& elem);

    Mix_Chunk* GetWallHitSound() { return wallHitSound; }
    Mix_Chunk* GetPaddleHitSound() { return paddleHitSound; }

private:

    vector<unique_ptr<UIElement>> Achievements;
};