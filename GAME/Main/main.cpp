
#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>

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
    bool accepted = false;

    int headCount = QInputDialog::getInt(
        nullptr,
        "New Game",
        "How many players?",
        2, // Default
        1, // Minimum
        4, // Maximum
        1, // Step
        &accepted);

    if (!accepted)
    {
        return 0;
    }

    // create a setup method which sets up UI & the game
    GameState game{SetupGame(headCount)};
   
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];
    ui.currentPlayerLabel->setText("Current player: " + QString::fromStdString(CurrentPlayer.Name));

    Connect_UI(game, ui);

        
    return app.exec();
}

