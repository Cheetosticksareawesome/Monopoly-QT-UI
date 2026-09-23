
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"
#include "UI-Helpers.h"
#include "jail.h"



void Connect_UI(Ui::MainWindow& ui, GameState& game)
{
    UpdatePlayerLabels(game, ui);
    //rollDice
    ui.rollDiceButton->setEnabled(!game.HasRolled);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [&ui, &game]()
    {
        UpdatePlayerLabels(game, ui);

        Player &player = game.Players[game.CurrentPlayerIndex];

        DiceRoll roll = RollDice();
        bool double_dice = roll.Die1 == roll.Die2;

        if (double_dice)
        {
            player.DoubleDiceCount++;
            if (!player.InJail && player.DoubleDiceCount >= 3)
            {
                SendToJail(player);
            }
            if(player.InJail)
            {
                player.DoubleDiceCount = 0;
                player.InJail = false;
            }
        }

        ui.diceLabel->setText(QString::number(roll.Die1) + " + " + QString::number(roll.Die2));
        MovePlayer(game, ui, (roll.Die1 + roll.Die2));
        UpdatePlayerLabels(game, ui);

        BoardSpace &CurrentTile = game.board.Spaces[player.Position];

        game.HasRolled = true;
        ui.buyButton->setEnabled(false);

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
            UpdatePlayerLabels(game, ui);
        }
        else
        {
            if(CurrentTile.OwnerIndex == -1 && (CurrentTile.Type == SpaceType::Property || CurrentTile.Type == SpaceType::Utility || CurrentTile.Type == SpaceType::TrainStation))
            {
                ui.buyButton->setEnabled(true);
            }
        }

        ui.rollDiceButton->setEnabled(double_dice && !player.InJail);
        ui.endTurnButton->setEnabled(!double_dice || player.InJail); 
    });

    //EndTurn
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

        game.HasRolled = false;
        ui.rollDiceButton->setEnabled(!game.HasRolled);
        ui.endTurnButton->setEnabled(game.HasRolled);
    });
    //buyProperty
    ui.buyButton->setEnabled(false);
    QObject::connect(ui.buyButton, &QPushButton::clicked, [&ui, &game]()
    {
        BuyProperty(game);
        UpdatePlayerLabels(game, ui);
        ui.buyButton->setEnabled(false);
    });

}