#pragma once

#include <string>
#include <vector>

struct GameState;
namespace Ui { class MainWindow; }

enum class EffectType
{
    //standard effects
    MovePlayer,
    EditMoney,
    JailPlayer,

    //custom Experimentals
    SummonWeather, //Destroy a random percentage of all player's houses
    HouseMarketCrash, //Random Rent multiplier (0.5x - 2x)
    ExtremeInflation, //Start Money *= 4 for diceroll amount of turns (group pot *=4 & any income in the group pot *= 4 for diceroll turnss).

};

struct Card 
{
    std::string Name;
    std::string Description;
    EffectType Effect;
    int MoneyAmount{0};
    int SetPlayerPosition{0};
    bool IsChanceCard{false};
    bool IsCommunityChest{false};
};

void ApplyCardEffect(GameState &game, Ui::MainWindow &ui, Card &card);

Card DrawCard(std::vector<Card> &Cards);

std::vector<Card> SetupCards();
void FilterCards(GameState &game, std::vector<Card> &cards);