
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"
#include "UI-Helpers.h"



void Connect_UI(Ui::MainWindow& ui, GameState& game)
{
    UpdatePlayerLabels(game, ui);

    ui.rollDiceButton->setEnabled(!game.HasRolled);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [&ui, &game]()
    {
        UpdatePlayerLabels(game, ui);

        DiceRoll roll = RollDice();
        bool double_dice = roll.Die1 == roll.Die2;

        ui.diceLabel->setText(QString::number(roll.Die1) + " + " + QString::number(roll.Die2));
        MovePlayer(game, (roll.Die1 + roll.Die2));
        UpdatePlayerLabels(game, ui);

        Player &player = game.Players[game.CurrentPlayerIndex];
        BoardSpace &CurrentTile = game.board.Spaces[player.Position];

        ui.positionLabel->setText(QString::fromStdString(CurrentTile.Name));

        if ((CurrentTile.Type == SpaceType::Property) || (CurrentTile.Type == SpaceType::TrainStation) || (CurrentTile.Type == SpaceType::Utility))
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

        if (CurrentTile.OwnerIndex != -1 && CurrentTile.OwnerIndex != game.CurrentPlayerIndex)
        {
            player.Money -= CurrentTile.Rent;
            game.Players[CurrentTile.OwnerIndex].Money += CurrentTile.Rent;
            UpdatePlayerLabels(game, ui);
        }
        else
        {
            if(CurrentTile.OwnerIndex == -1 && CurrentTile.Type == SpaceType::Property || CurrentTile.Type == SpaceType::Utility || CurrentTile.Type == SpaceType::TrainStation)
            {
                ui.buyButton->setEnabled(true);
            }
        }


        if(double_dice)
        {
            player.DoubleDiceCount++;
            if(player.DoubleDiceCount >= 3)
            {
                //SendToJail();
                player.DoubleDiceCount = 0;
            }
        }

        game.HasRolled = !game.HasRolled;
        ui.rollDiceButton->setEnabled(double_dice);
        ui.endTurnButton->setEnabled(!double_dice); }
    );

    ui.endTurnButton->setEnabled(game.HasRolled);
    QObject::connect(ui.endTurnButton, &QPushButton::clicked, [&ui, &game]()
    {
        EndTurn(game);

        Player &player = game.Players[game.CurrentPlayerIndex];
        BoardSpace &CurrentTile = game.board.Spaces[player.Position];

        ui.buyButton->setEnabled(false);
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
        BuyProperty(game);
        UpdatePlayerLabels(game, ui);
        ui.buyButton->setEnabled(false);
    });

}