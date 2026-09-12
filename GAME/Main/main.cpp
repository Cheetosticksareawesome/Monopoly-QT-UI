
#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "ui_MainUI.h"

#include "Player.h"
#include "GameState.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello Monopoly!" << std::endl;

    GameState game{};
    game.board = CreateBoard();

    Player player_1{
        "Player 1",
        1500, // Money
        0,    // Position
    };

    Player player_2{
        "Player 2",
        1500, // Money
        0,    // Position
    };

    game.Players.push_back(player_1);
    game.Players.push_back(player_2);

    //reference:
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    CurrentPlayer.Position += 3; //RollDice method here (rand int 1-12)

    std::cout << CurrentPlayer.Name << " is at " << game.board.Spaces[CurrentPlayer.Position].Name;

    return 0;
}
