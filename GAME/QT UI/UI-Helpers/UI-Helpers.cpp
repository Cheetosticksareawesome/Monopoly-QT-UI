#include "GameState.h"
#include "ui_MainUI.h"

#include <vector>

void BuyProperty(GameState& game, Ui::MainWindow& ui)
{
    Player& player = game.Players[game.CurrentPlayerIndex];
    BoardSpace& CurrentTile = game.board.Spaces[player.Position];

    const std::vector<QLabel *> playerPawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    const std::vector<QFrame *> tiles{
        ui.tile0, ui.tile1, ui.tile2, ui.tile3, ui.tile4,
        ui.tile5, ui.tile6, ui.tile7, ui.tile8, ui.tile9,
        ui.tile10, ui.tile11, ui.tile12, ui.tile13, ui.tile14,
        ui.tile15, ui.tile16, ui.tile17, ui.tile18, ui.tile19,
        ui.tile20, ui.tile21, ui.tile22, ui.tile23, ui.tile24,
        ui.tile25, ui.tile26, ui.tile27, ui.tile28, ui.tile29,
        ui.tile30, ui.tile31, ui.tile32, ui.tile33, ui.tile34,
        ui.tile35, ui.tile36, ui.tile37, ui.tile38, ui.tile39
    };

    if(player.Money >= CurrentTile.Price && CurrentTile.OwnerIndex == -1)
    {
        player.Money -= CurrentTile.Price;
        CurrentTile.OwnerIndex = game.CurrentPlayerIndex;
        tiles[player.Position]->setStyleSheet(playerPawns[game.CurrentPlayerIndex]->styleSheet());
    }
};

void UpdatePlayerLabels(GameState& game, Ui::MainWindow& ui)
{
    const std::vector<QLabel *> playerPawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    const std::vector<QLabel *> playerLabels{ui.player1, ui.player2, ui.player3, ui.player4};

    for(int i = 0; i < playerLabels.size(); i++)
    {   
        playerPawns[i]->setVisible(i < game.Players.size());
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

void UpdateCard(GameState& game, Ui::MainWindow& ui, Card card)
{
    ui.chanceText->setText(QString::fromStdString(card.Name + "\n\n" + card.Description));
}

void MovePawn(GameState& game, Ui::MainWindow& ui)
{
    std::vector<QLabel *> pawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    std::vector<QFrame *> tiles{
        ui.tile0, ui.tile1, ui.tile2, ui.tile3, ui.tile4,
        ui.tile5, ui.tile6, ui.tile7, ui.tile8, ui.tile9,
        ui.tile10, ui.tile11, ui.tile12, ui.tile13, ui.tile14,
        ui.tile15, ui.tile16, ui.tile17, ui.tile18, ui.tile19,
        ui.tile20, ui.tile21, ui.tile22, ui.tile23, ui.tile24,
        ui.tile25, ui.tile26, ui.tile27, ui.tile28, ui.tile29,
        ui.tile30, ui.tile31, ui.tile32, ui.tile33, ui.tile34,
        ui.tile35, ui.tile36, ui.tile37, ui.tile38, ui.tile39
    };

    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    pawns[game.CurrentPlayerIndex]->setParent(tiles[CurrentPlayer.Position]);
}
