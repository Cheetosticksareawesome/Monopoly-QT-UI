#pragma once

#include "GameState.h"
#include "ui_MainUI.h"

void BuyProperty(GameState& game);

void UpdatePlayerLabels(GameState &game, Ui::MainWindow &ui);
void UpdateChanceCard(GameState &game, Ui::MainWindow &ui, ChanceCard card);