#pragma once

#include "public/SimpleGameTypes.h"
#include "public/DataContainer.h"
#include "Tap.h"
#include "AchievementManager.h"
#include "Scene.h"
#include "public/Pong/Collision.h"
#include "public/Pong/Ball.h"
#include "Player.h"
#include "InputManager.h"
#include <iostream>
#include "RewardUIElement.h"

using std::shared_ptr;
using std::unique_ptr;

class GameLoop
{
public:

    void ReceiveData();
    void Start(); // Initialize this class
    void Run(); // Update this class

    void OnTap(Tap& tap); // Called when a tapping event happens
    void OnScore(const int score, const eGameSide _GetPlayer); // Called when one of the sides scores
    void OnMatchResult(const eGameSide _WinPlayer); // Called when the game session finishes

    void SetRewardChangedUI(std::vector<std::unique_ptr<sReward>>& _Rewards, eGameSide _RewardPlayer);

    Scene* GetScene() { return scene.get(); }
    unique_ptr<AchievementManager>& GetAchievementManager() { return achievementManager; }

private:

    // A dedicated data-container class holding all the required game data
    shared_ptr<DataContainer> dataContainer;
    
    // The class where all achievements are handled
    unique_ptr<AchievementManager> achievementManager;

    shared_ptr<Scene> scene;
       
    unique_ptr<Collision> collision;
    unique_ptr<Ball> ball;
    unique_ptr<Player> playerOne;
    unique_ptr<Player> playerTwo;

    // Player Score UI's
    unique_ptr<ScoreUIElement> playerOneScoreText;
    unique_ptr<ScoreUIElement> playerTwoScoreText;

    // Player Reward UI's
    unique_ptr<RewardUIElement> playerOneGoldUI;
    unique_ptr<RewardUIElement> playerOneDiamondUI;
    unique_ptr<RewardUIElement> playerTwoGoldUI;
    unique_ptr<RewardUIElement> playerTwoDiamondUI;
    
    // Inputs
    unique_ptr<InputManager> inputManager;

    bool running;

    // Input Buttons Press Check
    bool buttonOneUp = false;
    bool buttonOneDown = false;
    bool buttonTwoUp = false;
    bool buttonTwoDown = false;
    float dt = 0.0f;
};

