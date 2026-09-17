#pragma once

#include <vector>

#include "Player.h"
#include "board.h"

struct GameState
{
    std::vector<Player> Players;
    int CurrentPlayerIndex{0};
    Board board;
    bool HasRolled{false};
};

GameState SetupGame();

void MovePlayer(GameState& game, int steps);
void EndTurn(GameState& game);
