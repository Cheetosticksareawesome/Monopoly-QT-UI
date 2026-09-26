#include "GameState.h"
#include "ui_MainUI.h"

#include <vector>
#include <QGridLayout>

static std::vector<QWidget *> PawnAreas(Ui::MainWindow& ui)
{
    return {
        ui.tokenArea0, ui.tokenArea1, ui.tokenArea2, ui.tokenArea3, ui.tokenArea4,
        ui.tokenArea5, ui.tokenArea6, ui.tokenArea7, ui.tokenArea8, ui.tokenArea9,
        ui.tokenArea10, ui.tokenArea11, ui.tokenArea12, ui.tokenArea13, ui.tokenArea14,
        ui.tokenArea15, ui.tokenArea16, ui.tokenArea17, ui.tokenArea18, ui.tokenArea19,
        ui.tokenArea20, ui.tokenArea21, ui.tokenArea22, ui.tokenArea23, ui.tokenArea24,
        ui.tokenArea25, ui.tokenArea26, ui.tokenArea27, ui.tokenArea28, ui.tokenArea29,
        ui.tokenArea30, ui.tokenArea31, ui.tokenArea32, ui.tokenArea33, ui.tokenArea34,
        ui.tokenArea35, ui.tokenArea36, ui.tokenArea37, ui.tokenArea38, ui.tokenArea39
    };
}

void SetupPawnLayouts(GameState& game, Ui::MainWindow& ui)
{
    const auto areas = PawnAreas(ui);
    for(QWidget* area : areas)
    {
        area->setMaximumHeight(QWIDGETSIZE_MAX);
        area->setMinimumSize(52, 34);
        auto* grid = new QGridLayout(area);
        grid->setContentsMargins(0, 0, 0, 0);
        grid->setSpacing(2);
        for(int slot = 0; slot < 2; slot++)
        {
            grid->setRowMinimumHeight(slot, 16);
            grid->setColumnMinimumWidth(slot, 25);
            grid->setRowStretch(slot, 1);
            grid->setColumnStretch(slot, 1);
        }
    }

    const std::vector<QLabel *> pawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    for(int i = 0; i < pawns.size(); i++)
    {
        pawns[i]->setMinimumSize(25, 16);
        pawns[i]->setMaximumSize(25, 25);
        pawns[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
        int position = i < game.Players.size() ? game.Players[i].Position : 0;
        auto* grid = static_cast<QGridLayout*>(areas[position]->layout());
        grid->addWidget(pawns[i], i / 2, i % 2, Qt::AlignHCenter);
        pawns[i]->setVisible(i < game.Players.size());
    }
}

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
    // setup tooltips
    std::vector<int> indices;
    std::vector<QFrame *> tiles{
        ui.tile0, ui.tile1, ui.tile2, ui.tile3, ui.tile4,
        ui.tile5, ui.tile6, ui.tile7, ui.tile8, ui.tile9,
        ui.tile10, ui.tile11, ui.tile12, ui.tile13, ui.tile14,
        ui.tile15, ui.tile16, ui.tile17, ui.tile18, ui.tile19,
        ui.tile20, ui.tile21, ui.tile22, ui.tile23, ui.tile24,
        ui.tile25, ui.tile26, ui.tile27, ui.tile28, ui.tile29,
        ui.tile30, ui.tile31, ui.tile32, ui.tile33, ui.tile34,
        ui.tile35, ui.tile36, ui.tile37, ui.tile38, ui.tile39};

    for (int i = 0; i < game.board.Spaces.size(); i++)
    {
        if (game.board.Spaces[i].Type == SpaceType::Property || game.board.Spaces[i].Type == SpaceType::Utility || game.board.Spaces[i].Type == SpaceType::TrainStation)
        {
            indices.push_back(i);
        }
    }

    for (int index : indices)
    {
        if (auto* badge = tiles[index]->findChild<QLabel *>("HouseIcon" + QString::number(index)))
        {
            int houses = game.board.Spaces[index].HouseCount;
            badge->setText(houses >= 5 ? "HOTEL" : "H" + QString::number(houses));
            badge->setVisible(houses > 0);
        }
        std::string Mortgaged = game.board.Spaces[index].isMortgaged ? "true" : "false";

        tiles[index]->setToolTip(
            QString::fromStdString(game.board.Spaces[index].Name) 
            + QString::fromStdString(" \nType: ") 
            + QString::fromStdString(ToStdStringSpaceType(game.board.Spaces[index].Type)) 
            + QString::fromStdString(" \nPrice: ") 
            + QString::number(game.board.Spaces[index].Price) 
            + QString::fromStdString(" \nRent: ") 
            + QString::number(game.board.Spaces[index].Rent) 
            + QString::fromStdString(" \nMortage: ") 
            + QString::number(game.board.Spaces[index].Mortage) 
            + QString::fromStdString(" \nOwner: ") 
            + QString::fromStdString(PlayerIndexToName(game, game.board.Spaces[index].OwnerIndex)) 
            + QString::fromStdString(" \nProperty-Index: ") 
            + QString::number(index)
            + QString::fromStdString("\nIs-Mortgaged: ")
            + QString::fromStdString(Mortgaged)

        );
        tiles[index]->setToolTipDuration(60000);
    }
}

void UpdateCard(GameState& game, Ui::MainWindow& ui, Card card)
{
    if(card.IsCommunityChest)
    {
        ui.communityText->setText(QString::fromStdString(card.Name + "\n\n" + card.Description));
    }
    if(card.IsChanceCard)
    {
        ui.chanceText->setText(QString::fromStdString(card.Name + "\n\n" + card.Description));
    }
}

void MovePawn(GameState& game, Ui::MainWindow& ui)
{
    std::vector<QLabel *> pawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    const auto areas = PawnAreas(ui);
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];
    int index = game.CurrentPlayerIndex;
    auto* grid = static_cast<QGridLayout*>(areas[CurrentPlayer.Position]->layout());
    grid->addWidget(pawns[index], index / 2, index % 2, Qt::AlignHCenter);
    pawns[index]->show();
}
void MortgageProperty(GameState& game, Ui::MainWindow& ui, int PorpertyIndex)
{
    
}
