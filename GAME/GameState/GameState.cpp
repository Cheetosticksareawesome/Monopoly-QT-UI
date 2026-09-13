
#include <iostream>
#include <limits>

#include "GameState.h"

void MovePlayer(GameState &game, int steps)
{
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    CurrentPlayer.Position = (CurrentPlayer.Position + steps) % game.board.Spaces.size();
}

void EndTurn(GameState& game)
{
    game.CurrentPlayerIndex = (game.CurrentPlayerIndex + 1) % game.Players.size();
}

GameState SetupGame()
{
    int PlayerCount{};

    GameState game;
    game.board = CreateBoard();

    std::cout << "Enter The amount of Human players 1-4" << std::endl;
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