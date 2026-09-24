#pragma once

#include "GameState.h"
#include "ui_MainUI.h"


void UpdatePlayerLabels(GameState &game, Ui::MainWindow &ui);
void UpdateCard(GameState &game, Ui::MainWindow &ui, Card card);
void MovePawn(GameState &game, Ui::MainWindow &ui);
void SetupPawnLayouts(GameState &game, Ui::MainWindow &ui);
void BuyProperty(GameState &game, Ui::MainWindow &ui);
