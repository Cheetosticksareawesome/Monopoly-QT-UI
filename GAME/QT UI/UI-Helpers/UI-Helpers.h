#pragma once

#include "GameState.h"
#include "ui_MainUI.h"

void BuyProperty(GameState& game);

void UpdatePlayerLabels(GameState &game, Ui::MainWindow &ui);
void UpdateCard(GameState &game, Ui::MainWindow &ui, Card card);
void MovePawn(GameState &game, Ui::MainWindow &ui);