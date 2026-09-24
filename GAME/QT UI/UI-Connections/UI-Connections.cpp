
#include "UI-Connections.h"
#include "GameState.h"
#include "Dice.h"
#include "ui_MainUI.h"
#include "UI-Helpers.h"
#include "jail.h"
#include <QFrame>

void Connect_UI(GameState &game, Ui::MainWindow &ui)
{
    SetupPawnLayouts(game, ui);
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

        ui.chanceText->setText(QString::fromStdString(""));
        ui.communityText->setText(QString::fromStdString(""));

        game.HasRolled = false;
        ui.rollDiceButton->setEnabled(!game.HasRolled);
        ui.endTurnButton->setEnabled(game.HasRolled);
    });

    //buyProperty
    ui.buyButton->setEnabled(false);
    QObject::connect(ui.buyButton, &QPushButton::clicked, [&ui, &game]()
    {
        BuyProperty(game, ui);
        UpdatePlayerLabels(game, ui);
        ui.buyButton->setEnabled(false);
    });


    //toggle Mortgage

    //setup tooltips
    std::vector<int> indices;
    std::vector<QFrame *> tiles
    {
        ui.tile0, ui.tile1, ui.tile2, ui.tile3, ui.tile4,
        ui.tile5, ui.tile6, ui.tile7, ui.tile8, ui.tile9,
        ui.tile10, ui.tile11, ui.tile12, ui.tile13, ui.tile14,
        ui.tile15, ui.tile16, ui.tile17, ui.tile18, ui.tile19,
        ui.tile20, ui.tile21, ui.tile22, ui.tile23, ui.tile24,
        ui.tile25, ui.tile26, ui.tile27, ui.tile28, ui.tile29,
        ui.tile30, ui.tile31, ui.tile32, ui.tile33, ui.tile34,
        ui.tile35, ui.tile36, ui.tile37, ui.tile38, ui.tile39
    };

    for(int i = 0; i < game.board.Spaces.size(); i++)
    {
        if (game.board.Spaces[i].Type == SpaceType::Property || game.board.Spaces[i].Type == SpaceType::Utility || game.board.Spaces[i].Type == SpaceType::TrainStation)
        {
            indices.push_back(i);
        }
    }
    
    for(int index : indices)
    {
        tiles[index]->setToolTip(
            QString::fromStdString(game.board.Spaces[index].Name)     + QString::fromStdString(" \nType: ")
          + QString::fromStdString(ToStdStringSpaceType(game.board.Spaces[index].Type))     + QString::fromStdString(" \nPrice: ")
          + QString::number(game.board.Spaces[index].Price)           + QString::fromStdString(" \nRent: ")
          + QString::number(game.board.Spaces[index].Rent)            + QString::fromStdString(" \nMortage: ")
          + QString::number(game.board.Spaces[index].Mortage)         + QString::fromStdString(" \nOwner: ")
          + QString::fromStdString(PlayerIndexToName(game, game.board.Spaces[index].OwnerIndex))

        );
        tiles[index]->setToolTipDuration(60000);
    }
}

