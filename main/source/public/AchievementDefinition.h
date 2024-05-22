#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "SimpleGameTypes.h"

using std::string;
using std::vector;
using std::unique_ptr;

struct sReward
{
    eCurrencyType CurrencyType;
    int CurrencyAmount;

    sReward() : CurrencyType(eCurrencyType::GOLD), CurrencyAmount(0)
    {}

    sReward(eCurrencyType _CurrencyType, int _CurrencyAmount) : CurrencyType(_CurrencyType), CurrencyAmount(_CurrencyAmount)
    {}
};

// A data class holding the definition of an achievement.
class AchievementDefinition
{
public:

    AchievementDefinition() : Key(""), ImagePath(""), Title(""), Text(""), WinCondition(1)
    { }

    AchievementDefinition(string _Key, string _ImagePath, string _Title, string _Text, int _WinCondition) : Key(_Key), ImagePath(_ImagePath), Title(_Title), Text(_Text), WinCondition(_WinCondition)
    { }

    string Key;
    string ImagePath;
    string Title;
    string Text;
    int WinCondition;
    vector<unique_ptr<sReward>> Rewards;
};