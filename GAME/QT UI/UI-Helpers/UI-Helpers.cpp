#include "GameState.h"
#include "ui_MainUI.h"

#include <vector>

void BuyProperty(GameState& game)
{
    Player& player = game.Players[game.CurrentPlayerIndex];
    BoardSpace& CurrentTile = game.board.Spaces[player.Position];

    if(player.Money >= CurrentTile.Price && CurrentTile.OwnerIndex == -1)
    {
        player.Money -= CurrentTile.Price;
        CurrentTile.OwnerIndex = game.CurrentPlayerIndex;
    }
};

void UpdatePlayerLabels(GameState& game, Ui::MainWindow& ui)
{
    std::vector<QLabel *> playerPawns;
    std::vector<QLabel *> playerLabels;

    if(playerLabels.size() > 1 || playerPawns.size() > 1)
    {
        playerPawns.push_back(ui.Pawn1);
        playerPawns.push_back(ui.Pawn2);
        playerPawns.push_back(ui.Pawn3);
        playerPawns.push_back(ui.Pawn4);

        playerLabels.push_back(ui.player1);
        playerLabels.push_back(ui.player2);
        playerLabels.push_back(ui.player3);
        playerLabels.push_back(ui.player4);
    }

    for(int i = 0; i < playerLabels.size(); i++)
    {   
        if(i < game.Players.size())
        {
            playerLabels[i]->show();
            playerLabels[i]->setText(QString::fromStdString(game.Players[i].Name) + "|" + "€ " + QString::number(game.Players[i].Money));
        }
        else
        {
            playerLabels[i]->hide();
        }
    }

    for(int i = 0; i < playerPawns.size(); i++)
    {
        playerPawns[i]->setParent(ui.boardLayout[i]);
    }
}

void UpdateCard(GameState& game, Ui::MainWindow& ui, Card card)
{
    ui.chanceText->setText(QString::fromStdString(card.Name + "\n\n" + card.Description));
}