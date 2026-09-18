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
    std::vector<QLabel*> playerLabels;
    playerLabels.push_back(ui.player1);
    playerLabels.push_back(ui.player2);
    playerLabels.push_back(ui.player3);
    playerLabels.push_back(ui.player4);

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
}