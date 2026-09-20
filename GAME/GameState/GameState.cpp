
#include <iostream>
#include <limits>

#include "GameState.h"
#include "jail.h"
#include "DrawableCards.h"
#include "logger-manager.h"

#include "UI-Helpers.h"
#include "ui_MainUI.h"
#include "UI-Connections.h"


void MovePlayer(GameState& game, Ui::MainWindow& ui, int steps)
{
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];
    steps = CurrentPlayer.InJail ? 0 : steps;

    if((CurrentPlayer.Position + steps) >= game.board.Spaces.size())
    {
        CurrentPlayer.Money += 200;
    }

    CurrentPlayer.Position = (CurrentPlayer.Position + steps) % game.board.Spaces.size();

    BoardSpace& CurrentSpace = game.board.Spaces[CurrentPlayer.Position];
    
    switch (game.board.Spaces[CurrentPlayer.Position].Type)
    {
    case SpaceType::GoToJail:
        SendToJail(CurrentPlayer);
        break;
    case SpaceType::Chance:
        if (!game.ChanceCards.empty())
        {
            DrawCard(game.ChanceCards);
        }
        break;
    case SpaceType::Community_Chest:
        if (!game.CommunityChests.empty())
        {
            DrawCard(game.CommunityChests);
        }
        break;
    case SpaceType::Free_Parking:
        break;
    case SpaceType::IncomeTax:
        CurrentPlayer.Money -= 200;
        break;
    case SpaceType::Luxury_Tax:
        CurrentPlayer.Money -= 100;
        break;
    case SpaceType::Property:
    case SpaceType::Utility:
    case SpaceType::TrainStation:
        break;

    default:
        break;
    }
    UpdatePlayerLabels(game, ui);
}

void EndTurn(GameState& game)
{
    Player& player = game.Players[game.CurrentPlayerIndex];
    player.DoubleDiceCount = 0;

    if(player.InJail)
    {
        player.JailTurns++;
        if(player.JailTurns >= 3)
        {
            player.InJail = false;
            player.JailTurns = 0;
        }
    }

    game.CurrentPlayerIndex = (game.CurrentPlayerIndex + 1) % game.Players.size();
}

GameState SetupGame(int PlayerCount)
{
    GameState game;
    game.board = CreateBoard();

    std::vector<Card> cards = SetupCards();
    FilterCards(game, cards);

    int count{1};
    while(0 < PlayerCount)
    {
        Player player = {
            "player_"+std::to_string(count),
            1500,
            0
        };

        game.Players.push_back(player);
        count++;
        PlayerCount--;
    }

    return game;
}
