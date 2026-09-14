
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

    ui.rollDiceButton->setEnabled(true);
    QObject::connect(ui.rollDiceButton, &QPushButton::clicked, [ui]()
    {
        int roll = RollDice();
        ui.diceLabel->setText(QString::number(roll));
    });

    window.show();
    //++


    std::cout << "Hello Monopoly!" << std::endl;

    // Temporary players: console input would block Qt's event loop here.
    GameState game{};
    game.board = CreateBoard();
    game.Players = {{"player_1", 1500, 0}, {"player_2", 1500, 0}};

    /*
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
    */
    
    return app.exec();
}

