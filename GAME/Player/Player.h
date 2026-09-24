#pragma once

#include <string>

struct GameState;

struct Player
{
    std::string Name;
    int Money{0};
    int Position{0};
    int DoubleDiceCount{0};
    bool InJail{false};
    int JailTurns{0};
};

std::string PlayerIndexToName(GameState& game, int& playerIndex);
