
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"



void Connect_UI(Ui::MainWindow& ui, GameState& game)
{

    ui.rollDiceButton->setEnabled(!game.HasRolled);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [&ui, &game]()
    {

        int roll = RollDice();
        ui.diceLabel->setText(QString::number(roll));
        MovePlayer(game, roll);

        Player &player = game.Players[game.CurrentPlayerIndex];
        BoardSpace &CurrentTile = game.board.Spaces[player.Position];

        ui.positionLabel->setText(QString::fromStdString(CurrentTile.Name));

        if (CurrentTile.Type == SpaceType::Property || CurrentTile.Type == SpaceType::TrainStation || CurrentTile.Type == SpaceType::Utility)
        {
            ui.propertyDetails->setText(
                QString::fromStdString("Name: " + CurrentTile.Name) + "\nPrice: "
              + QString::number(CurrentTile.Price) + "\nRent: "
              + QString::number(CurrentTile.Rent) + "\nMortage: "
              + QString::number(CurrentTile.Mortage)

            );
        }

        else
        {
            ui.propertyDetails->setText(QString::fromStdString("Name: " + CurrentTile.Name));
        }
        
        game.HasRolled = !game.HasRolled;
        ui.rollDiceButton->setEnabled(!game.HasRolled);
        ui.endTurnButton->setEnabled(game.HasRolled);
    });

    
    ui.endTurnButton->setEnabled(game.HasRolled);
    QObject::connect(ui.endTurnButton, &QPushButton::clicked, [&ui, &game]()
    {
        EndTurn(game);

        Player &player = game.Players[game.CurrentPlayerIndex];
        BoardSpace &CurrentTile = game.board.Spaces[player.Position];

        ui.currentPlayerLabel->setText(QString::fromStdString("Current player: " + game.Players[game.CurrentPlayerIndex].Name));
        ui.positionLabel->setText(QString::fromStdString(CurrentTile.Name));

        if (CurrentTile.Type == SpaceType::Property || CurrentTile.Type == SpaceType::TrainStation || CurrentTile.Type == SpaceType::Utility)
        {
            ui.propertyDetails->setText(
                QString::fromStdString("Name: " + CurrentTile.Name) + "\nPrice: "
              + QString::number(CurrentTile.Price) + "\nRent: "
              + QString::number(CurrentTile.Rent) + "\nMortage: "
              + QString::number(CurrentTile.Mortage)

            );
        }

        else{ ui.propertyDetails->setText(QString::fromStdString("Name: " + CurrentTile.Name)); }

        game.HasRolled = !game.HasRolled;
        ui.rollDiceButton->setEnabled(!game.HasRolled);
        ui.endTurnButton->setEnabled(game.HasRolled);
    });

    ui.buyButton->setEnabled(false);
    QObject::connect(ui.buyButton, &QPushButton::clicked, [&ui, &game]()
    {

    });

}