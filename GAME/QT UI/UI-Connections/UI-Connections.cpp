
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"

void Connect_UI(Ui::MainWindow ui, GameState game)
{

    ui.rollDiceButton->setEnabled(true);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [&ui, &game]()
    {
    int roll = RollDice();
    ui.diceLabel->setText(QString::number(roll));
    MovePlayer(game, roll);
    ui.positionLabel->setText(QString::fromStdString(game.board.Spaces[game.Players[game.CurrentPlayerIndex].Position].Name)); 
    });


    ui.endTurnButton->setEnabled(true);
    QObject::connect(ui.endTurnButton, &QPushButton::clicked, [&ui, &game]()
    {
    EndTurn(game);
    ui.currentPlayerLabel->setText(QString::fromStdString("Current player: " + game.Players[game.CurrentPlayerIndex].Name));
    });


}