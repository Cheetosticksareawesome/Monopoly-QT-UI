#pragma once

#include <string>

enum EffectType
{
    //standard effects
    MovePlayer,
    EditMoney,

    //custom Experimentals
    SummonWeather, //Destroy a random percentage of all player's houses
    HouseMarketCrash, //Random Rent multiplier (0.5x - 2x)
    ExtremeInflation, //Start Money *= 4 for diceroll amount of turns (group pot *=4 & any income in the group pot *= 4 for diceroll turnss).

};

struct ChanceCard 
{
    std::string Name;
    std::string Description;
    EffectType Effect;
    int MoneyAmount{0};
    int SetPlayerPosition{0};
};

struct Community_Chest
{
    std::string Name;
    std::string Description;
    EffectType Effect;
    int MoneyAmount{0};
    int SetPlayerPosition{0};
};

ChanceCard DrawChanceCard();