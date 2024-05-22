#include "public/AchievementManager.h"
#include "public/Scene.h"
#include "public/GameLoop.h"


AchievementManager::AchievementManager(std::shared_ptr<DataContainer> _dataContainer, GameLoop* _GameLoop) : dataContainer(_dataContainer), gameLoop(_GameLoop)
{
}

AchievementManager::~AchievementManager()
{
	gameLoop = nullptr;
}

void AchievementManager::SetAchievementProgress(std::string _AchievementKey, int _AddedProgressCount, std::unique_ptr<Player>& _AffectPlayer)
{
	size_t playerAchievementCount = _AffectPlayer->GetAchievements().size();
	// Checks whether the number of achievement progress the player has earned is greater than 0. The reason for this is; If the player has not been able to progress any achievement, 
	// a new achievement will be created and given to the player without any checks, as there is no achievement to progress.
	if (playerAchievementCount > 0)
	{
		// If the player has never progressed to the achievement we are looking for, this value will remain incorrect and a new achievement will be created and given to the player.
		bool bIsFind = false;
		// The player's progress and achievements are checked.
		for (size_t i = 0; i < _AffectPlayer->GetAchievements().size(); i++)
		{
			if (_AffectPlayer->GetAchievements()[i]->AchievementKey == _AchievementKey)
			{
				bIsFind = true;
				// If the player achieved the achievement it needs to be triggered again.
				if (_AffectPlayer->GetAchievements()[i]->bIsAchieved)
					return;
				
				std::unique_ptr<sAchievement>& achievement = _AffectPlayer->GetAchievements()[i];

				// Increases the player's achievement progress value.
				achievement->ProgressCount += _AddedProgressCount;

				// If the player meets the achievement's win condition, the Achievement UI appears on the screen and gives the player his/her rewards.
				if (achievement->ProgressCount >= achievement->WinCondition)
				{
					achievement->bIsAchieved = true;

					for (size_t i = 0; i < dataContainer.get()->GetAchievementDefinitions().size(); i++)
					{
						if (dataContainer->GetAchievementDefinitions()[i]->Key == achievement->AchievementKey)
						{
							// Position calculation so that the Achievement UI appears on the player's side
							int Width = 200 + static_cast<int>(50 * 1.3f);
							if (_AffectPlayer->GetData()->GetPlayerSide() == eGameSide::OPPONENT)
							{
								Width = WINDOW_WIDTH;
								// Reward values in the UI are update.
								gameLoop->SetRewardChangedUI(dataContainer->GetAchievementDefinitions()[i]->Rewards, eGameSide::OPPONENT);
							}
							else
							{
								// Reward values in the UI are updated.
								gameLoop->SetRewardChangedUI(dataContainer->GetAchievementDefinitions()[i]->Rewards, eGameSide::PLAYER);
							}
							std::unique_ptr<UIElement> newUI = std::make_unique<UIElement>(
								Vec2(static_cast<float>(Width), WINDOW_HEIGHT),
								gameLoop->GetScene(),
								_AffectPlayer->GetData()->GetPlayerSide(),
								dataContainer->GetAchievementDefinitions()[i]->ImagePath, 
								dataContainer->GetAchievementDefinitions()[i]->Title,
								dataContainer->GetAchievementDefinitions()[i]->Text,
								20.f);
							// Adds the Achievement UI to the scene.
							gameLoop->GetScene()->Add(newUI);
							// Adds rewards to the player.
							_AffectPlayer->AddRewards(dataContainer->GetAchievementDefinitions()[i]->Rewards);
							return;
						}
					}
					return;
				}
			}
		}
		if (bIsFind == false)// If the player does not have this achievement's progress, he creates a new one and adds it to the player.
		{
			CreateAndAddAchievementProgress(_AchievementKey, _AddedProgressCount, _AffectPlayer);
		}
	}
	else // If the player does not have this achievement's progress, he creates a new one and adds it to the player.
	{
		CreateAndAddAchievementProgress(_AchievementKey, _AddedProgressCount, _AffectPlayer);
	}
}

void AchievementManager::CreateAndAddAchievementProgress(std::string _AchievementKey, int _AddedProgressCount, std::unique_ptr<Player>& _AffectPlayer)
{
	size_t arrSize = dataContainer->GetAchievementDefinitions().size();
	// The player's progress and achievements are checked.
	for (size_t i = 0; i < arrSize; i++)
	{
		if (dataContainer->GetAchievementDefinitions()[i]->Key == _AchievementKey)
		{
			// Here a new achievement is created and added to the player.
			sAchievement newAchievement;
			newAchievement.AchievementKey = dataContainer->GetAchievementDefinitions()[i]->Key;
			newAchievement.WinCondition = dataContainer->GetAchievementDefinitions()[i]->WinCondition;
			newAchievement.ProgressCount = _AddedProgressCount;
			if (newAchievement.ProgressCount >= dataContainer->GetAchievementDefinitions()[i]->WinCondition)
			{
				newAchievement.bIsAchieved = true; 
				// Position calculation so that the Achievement UI appears on the player's side
				int Width = 200 + static_cast<int>(50 * 1.3f);
				if (_AffectPlayer->GetData()->GetPlayerSide() == eGameSide::OPPONENT)
				{
					Width = WINDOW_WIDTH;
					// Reward values in the UI are updated.
					gameLoop->SetRewardChangedUI(dataContainer->GetAchievementDefinitions()[i]->Rewards, eGameSide::OPPONENT);
				}
				else
				{
					// Reward values in the UI are updated.
					gameLoop->SetRewardChangedUI(dataContainer->GetAchievementDefinitions()[i]->Rewards, eGameSide::PLAYER);
				}
				
				std::unique_ptr<UIElement> newUI = std::make_unique<UIElement>(
					Vec2(static_cast<float>(Width), WINDOW_HEIGHT),
					gameLoop->GetScene(),
					_AffectPlayer->GetData()->GetPlayerSide(),
					dataContainer->GetAchievementDefinitions()[i]->ImagePath,
					dataContainer->GetAchievementDefinitions()[i]->Title,
					dataContainer->GetAchievementDefinitions()[i]->Text,
					20.f);
				// Adds the Achievement UI to the scene.
				gameLoop->GetScene()->Add(newUI);
				// Adds rewards to the player.
				_AffectPlayer->AddRewards(dataContainer->GetAchievementDefinitions()[i]->Rewards);
			}
			_AffectPlayer->GetAchievements().push_back(std::make_unique<sAchievement>(newAchievement));
			return;
		}
	}
}
