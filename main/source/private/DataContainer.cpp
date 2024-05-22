#include "public/DataContainer.h"

DataContainer::DataContainer()
{
	// Here achievements and rewards are created and filled into the "achievementdefs" list.
	std::unique_ptr<AchievementDefinition> newAchievement = std::make_unique<AchievementDefinition>("Ach1", "resources/images/Ach1.bmp", "First tap", "Congratulations, you clicked for the first time!", 1);
	std::unique_ptr<sReward> newReward = std::make_unique<sReward>(eCurrencyType::GOLD, 5);
	newAchievement->Rewards.push_back(std::move(newReward));
	achievementDefs.push_back(std::move(newAchievement));

	newAchievement = std::make_unique<AchievementDefinition>("Ach2", "resources/images/Ach2.bmp", "100th tap", "Congratulations, you clicked for the hunder time!", 100);
	newReward = std::make_unique<sReward>(eCurrencyType::GOLD, 500);
	newAchievement->Rewards.push_back(std::move(newReward));
	achievementDefs.push_back(std::move(newAchievement));

	newAchievement = std::make_unique<AchievementDefinition>("Ach3", "resources/images/Ach3.bmp", "First score", "Congratulations, you earned your first score!", 1);
	newReward = std::make_unique<sReward>(eCurrencyType::GOLD, 500);
	newAchievement->Rewards.push_back(std::move(newReward));
	newReward = std::make_unique<sReward>(eCurrencyType::DIAMOND, 5);
	newAchievement->Rewards.push_back(std::move(newReward));
	achievementDefs.push_back(std::move(newAchievement));

	newAchievement = std::make_unique<AchievementDefinition>("Ach4", "resources/images/Ach4.bmp", "First win", "Congratulations, you won for the first time!", 1);
	newReward = std::make_unique<sReward>(eCurrencyType::DIAMOND, 15);
	newAchievement->Rewards.push_back(std::move(newReward));
	achievementDefs.push_back(std::move(newAchievement));
}

const std::vector<std::unique_ptr<AchievementDefinition>>& DataContainer::GetAchievementDefinitions()
{
	return achievementDefs;
}