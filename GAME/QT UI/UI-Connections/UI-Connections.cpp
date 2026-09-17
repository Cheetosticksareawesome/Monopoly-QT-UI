
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"



void Connect_UI(Ui::MainWindow& ui, GameState& game)
{

    ui.rollDiceButton->setEnabled(true);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [&ui, &game]()
    {
        Player& player = game.Players[game.CurrentPlayerIndex];
        BoardSpace& CurrentTile = game.board.Spaces[player.Position];

        int roll = RollDice();
        ui.diceLabel->setText(QString::number(roll));
        MovePlayer(game, roll);
        ui.positionLabel->setText(QString::fromStdString(CurrentTile.Name));
        ui.propertyDetails->setText(
           QString::fromStdString("Name: " + CurrentTile.Name) + "\nPrice: "
         + QString::number(CurrentTile.Price) + "\nRent: " 
         + QString::number(CurrentTile.Rent) + "\nMortage: " 
         + QString::number(CurrentTile.Mortage)
        
        ); 
    });

    
    ui.endTurnButton->setEnabled(true);
    QObject::connect(ui.endTurnButton, &QPushButton::clicked, [&ui, &game]()
    {
    EndTurn(game);
    ui.currentPlayerLabel->setText(QString::fromStdString("Current player: " + game.Players[game.CurrentPlayerIndex].Name));
    });
}