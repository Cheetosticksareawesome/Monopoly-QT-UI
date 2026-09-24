#include <QApplication>
#include <QMainWindow>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "GameState.h"
#include "UI-Connections.h"

struct Stats {
    long long count=0, gain=0, loss=0, flat=0, positive=0, negative=0;
    void add(long long delta) {
        count++;
        if(delta>0) {gain++; positive+=delta;}
        else if(delta<0) {loss++; negative+=delta;}
        else flat++;
    }
    void print(std::ostream& out, const char* name) {
        out << name << ": samples=" << count << ", gain%=" << gain*100.0/count
            << ", loss%=" << loss*100.0/count << ", unchanged%=" << flat*100.0/count
            << ", net average=" << (positive+negative)*1.0/count
            << ", average winning move=" << (gain?positive*1.0/gain:0)
            << ", average losing move=" << (loss?negative*1.0/loss:0) << "\n";
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);
    auto game=SetupGame(4);
    Connect_UI(game,ui);
    Stats movement, purchases, total;
    int rolls=0, bought=0;
    long long highest=1500, lowest=1500;
    auto trackCash = [&]() {
        for(const auto& p : game.Players) {
            highest = std::max(highest, static_cast<long long>(p.Money));
            lowest = std::min(lowest, static_cast<long long>(p.Money));
        }
    };
    while(rolls<100000) {
        if(ui.rollDiceButton->isEnabled()) {
            int index=game.CurrentPlayerIndex;
            long long before=game.Players[index].Money, allBefore=0;
            for(const auto& p:game.Players) allBefore+=p.Money;
            ui.rollDiceButton->click();
            trackCash();
            movement.add(game.Players[index].Money-before);
            auto& p=game.Players[index];
            auto& tile=game.board.Spaces[p.Position];
            if(ui.buyButton->isEnabled() && tile.OwnerIndex==-1 && p.Money>=tile.Price) {
                ui.buyButton->click();
                trackCash();
                bought++;
            }
            purchases.add(p.Money-before);
            long long allAfter=0;
            for(const auto& player:game.Players) allAfter+=player.Money;
            total.add(allAfter-allBefore);
            rolls++;
        } else if(ui.endTurnButton->isEnabled()) {
            ui.endTurnButton->click();
        } else break;
    }
    std::ofstream out("build/money-stats.txt");
    out << std::fixed << std::setprecision(4);
    out << "Four players; buy all affordable available properties; real random dice/cards; synchronous Qt button callbacks; no rendering/event-pump delays.\n";
    out << "Rolls=" << rolls << ", purchases=" << bought << "\n";
    movement.print(out,"Active player, movement only");
    purchases.print(out,"Active player, including purchases");
    total.print(out,"Combined cash of all players, including purchases");
    std::ofstream basic("build/money-basic.txt");
    basic << std::fixed << std::setprecision(2);
    basic << "Total income (net, all players): " << total.positive+total.negative << "\n";
    basic << "Highest cash achieved: " << highest << "\n";
    basic << "Highest debt achieved / lowest money: " << lowest << "\n";
    basic << "Average gain per roll (net, active player): " << (purchases.positive+purchases.negative)*1.0/rolls << "\n";
}
