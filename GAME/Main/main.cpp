
#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "ui_MainUI.h"

#include "Player.h"
#include "GameState.h"
#include "Dice.h"

int main(int argc, char *argv[])
{
    //QT:
    QApplication app(argc, argv);
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);


    window.show();
    //++

    std::cout << "Hello Monopoly!" << std::endl;

    // Temporary players: console input would block Qt's event loop here.
    // create a setup method which sets up UI & the game
    GameState game{};
    game.board = CreateBoard();
    game.Players = {{"player_1", 1500, 0}, {"player_2", 1500, 0}};
    


    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];
    ui.currentPlayerLabel->setText("Current player: " + QString::fromStdString(CurrentPlayer.Name));



    /*
    for(int i = 0; i < game.Players.size(); i++)
    {
    
    int roll = RollDice();
    std::cout << CurrentPlayer.Name << " Rolled " << roll << std::endl;

    MovePlayer(game, roll);
    std::cout << CurrentPlayer.Name << " landed on " << game.board.Spaces[CurrentPlayer.Position].Name << std::endl;


    EndTurn(game);
    ui.currentPlayerLabel->setText("current player: " + QString::fromStdString(CurrentPlayer.Name));
    }
    */
        
    return app.exec();
}

