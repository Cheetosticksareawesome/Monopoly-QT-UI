#pragma once

#include <vector>

#include "Player.h"
#include "board.h"

struct GameState
{
    std::vector<Player> Players;
    int CurrentPlayerIndex{0};
    Board board;
};

void MoveCurrentPlayer(GameState& game, int steps);