
#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "ui_MainUI.h"

#include "Player.h"
#include "GameState.h"
#include "Dice.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello Monopoly!" << std::endl;

    auto game = SetupGame();

    for(int i = 0; i < game.Players.size(); i++)
    {

    //reference:
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    std::cout << "Current turn: " << CurrentPlayer.Name << std::endl;


    int roll = RollDice();
    std::cout << CurrentPlayer.Name << " Rolled " << roll << std::endl;

    MovePlayer(game, roll);
    std::cout << CurrentPlayer.Name << " landed on " << game.board.Spaces[CurrentPlayer.Position].Name << std::endl;


    EndTurn(game);
    }

    
    return 0;
}
