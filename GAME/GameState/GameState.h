#pragma once

#include <vector>

#include "Player.h"
#include "board.h"
#include "DrawableCards.h"

#include "ui_MainUI.h"

struct GameState
{
    int CurrentPlayerIndex{0};
    bool HasRolled{false};

    std::vector<Player> Players;
    std::vector<Card> ChanceCards;
    std::vector<Card> CommunityChests;
    Board board;
};

GameState SetupGame(int PlayerCount);

void MovePlayer(GameState& game, Ui::MainWindow& ui, int steps);
void EndTurn(GameState& game);
