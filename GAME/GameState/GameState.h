#pragma once

#include <vector>

#include "Player.h"
#include "board.h"
#include "DrawableCards.h"


struct GameState
{
    int CurrentPlayerIndex{0};
    bool HasRolled{false};

    std::vector<Player> Players;
    std::vector<ChanceCard> ChanceCards;
    std::vector<Community_Chest> Community_Chests;
    Board board;
};

GameState SetupGame();

void MovePlayer(GameState& game, Ui::MainWindow& ui, int steps);
void EndTurn(GameState& game);
