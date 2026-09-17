
#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "UI-Connections.h"
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

    
    // create a setup method which sets up UI & the game
    GameState game{};
    game.board = CreateBoard();
    game.Players = {{"player_1", 1500, 0}, {"player_2", 1500, 0}};
    

    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];
    ui.currentPlayerLabel->setText("Current player: " + QString::fromStdString(CurrentPlayer.Name));

    


    Connect_UI(ui, game);
        
    return app.exec();
}

