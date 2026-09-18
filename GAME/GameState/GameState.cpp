
#include <iostream>
#include <limits>

#include "GameState.h"

void MovePlayer(GameState& game, int steps)
{
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    if((CurrentPlayer.Position + steps) >= game.board.Spaces.size())
    {
        CurrentPlayer.Money += 200;
    }

    if(CurrentPlayer.InJail)
    {
        steps = 0;
    }
    CurrentPlayer.Position = (CurrentPlayer.Position + steps) % game.board.Spaces.size();
}

void EndTurn(GameState& game)
{
    Player& player = game.Players[game.CurrentPlayerIndex];
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

GameState SetupGame()
{
    int PlayerCount{};
    GameState game;
    game.board = CreateBoard();

    
    while(true){
        if(std::cin >> PlayerCount)
        {
            if(PlayerCount > 0 && PlayerCount < 5)
            {
                break;
            }
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Invalide input! (only integers 1-4)" << std::endl;
    }

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