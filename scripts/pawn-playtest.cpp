#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <fstream>
#include <algorithm>
#include "GameState.h"
#include "UI-Connections.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::ofstream log("build/playtest-run.md");
    log << "# Gameplay test — 2026-09-25\n\n"
        << "Automated Qt integration playthrough using the project's compiled game code and actual QPushButton::click() connections. Four players, normal random dice/cards, buy whenever affordable. No game-state manipulation. Offscreen Qt platform; this is not manual desktop testing.\n\n";
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);
    auto game = SetupGame(4);
    Connect_UI(game, ui);
    window.show();
    app.processEvents();
    std::vector<QLabel*> pawns{ui.Pawn1, ui.Pawn2, ui.Pawn3, ui.Pawn4};
    log << "## Resize checks\n\n";
    for(auto size : {QSize(1120,820), QSize(900,600), QSize(1400,1000), QSize(1120,820)})
    {
        window.resize(size);
        app.processEvents();
        log << "- Requested " << size.width() << "x" << size.height()
            << "; actual " << window.width() << "x" << window.height() << ".";
        bool visible = true, overlap = false;
        for(int i=0;i<4;i++)
        {
            visible &= pawns[i]->isVisible() && pawns[i]->parentWidget()->rect().contains(pawns[i]->geometry());
            for(int j=0;j<i;j++)
                overlap |= pawns[i]->parentWidget() == pawns[j]->parentWidget() && pawns[i]->geometry().intersects(pawns[j]->geometry());
        }
        log << " All pawns visible and inside parent: " << (visible?"yes":"NO")
            << "; overlapping: " << (overlap?"YES":"no") << ".\n";
    }
    window.grab().save("build/playtest-start.png");
    log << "\n## Playthrough\n\n| Roll | Player | Dice | Position | Purchase | Cash P1 / P2 / P3 / P4 |\n|---|---|---|---|---|---|\n";
    int rolls=0, turns=0, mismatches=0, staleOwners=0;
    std::string stop;
    while(true)
    {
        if(std::all_of(game.Players.begin(),game.Players.end(),[](const Player& p){return p.Money<0;}))
        { stop="All four players have negative cash."; break; }
        if(!ui.rollDiceButton->isEnabled() && !ui.endTurnButton->isEnabled())
        { stop="Cannot progress: both Roll Dice and End Turn are disabled."; break; }
        if(rolls >= 100000)
        { stop="Runner safety limit (100,000 rolls); game still able to progress. Requested endpoint not reached."; break; }
        if(ui.rollDiceButton->isEnabled())
        {
            int index=game.CurrentPlayerIndex;
            ui.rollDiceButton->click();
            app.processEvents();
            rolls++;
            auto& player=game.Players[index];
            auto& tile=game.board.Spaces[player.Position];
            std::string purchase="-";
            if(ui.buyButton->isEnabled() && tile.OwnerIndex==-1 && player.Money>=tile.Price)
            {
                ui.buyButton->click();
                app.processEvents();
                purchase=tile.Name;
                auto* frame=window.findChild<QFrame*>("tile"+QString::number(player.Position));
                if(frame->toolTip().contains("Unowned")) staleOwners++;
            }
            log << "| " << rolls << " | " << index+1 << " | " << ui.diceLabel->text().toStdString()
                << " | " << player.Position << " | " << purchase << " | ";
            for(auto& p:game.Players) log << p.Money << " / ";
            log << "|\n";
            auto expected="tokenArea"+QString::number(player.Position);
            if(pawns[index]->parentWidget()->objectName()!=expected)
            {
                mismatches++;
                log << "\nPawn mismatch after roll " << rolls << ": P" << index+1
                    << " logical position " << player.Position << ", pawn parent "
                    << pawns[index]->parentWidget()->objectName().toStdString() << ".\n\n";
            }
            if(rolls%10==0) { window.resize(rolls%20?QSize(900,600):QSize(1400,1000)); app.processEvents(); }
            log.flush();
        }
        else if(ui.endTurnButton->isEnabled())
        {
            ui.endTurnButton->click();
            app.processEvents();
            turns++;
        }
    }
    window.grab().save("build/playtest-final.png");
    log << "\n## Result\n\n" << stop << "\n\nRolls: " << rolls << ". End-turn clicks: " << turns
        << ". Pawn position mismatches: " << mismatches << ". Purchased tiles still labelled Unowned: " << staleOwners << ".\n\n";
    for(int i=0;i<4;i++) log << "- P" << i+1 << ": cash " << game.Players[i].Money << ", position "
        << game.Players[i].Position << ", in jail " << game.Players[i].InJail << ".\n";
    log << "\nCurrent player: P" << game.CurrentPlayerIndex+1 << ". Last dice: "
        << ui.diceLabel->text().toStdString() << ". Roll enabled: " << ui.rollDiceButton->isEnabled()
        << ". End Turn enabled: " << ui.endTurnButton->isEnabled() << ".\n";
}
