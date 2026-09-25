#include <QApplication>
#include <QMainWindow>
#include <fstream>
#include "GameState.h"
#include "UI-Connections.h"
#include "Dice.h"
DiceRoll RollDice() { return {1,2}; }
int RollDie() { return 1; }
struct Fixture {
    QMainWindow window;
    Ui::MainWindow ui;
    GameState game{SetupGame(2)};
    Fixture() { ui.setupUi(&window); Connect_UI(game,ui); ui.MortgageField->setText("3"); }
};
int main(int argc,char**argv) {
    QApplication app(argc,argv);
    std::ofstream out("mortgage-tests.md");
    out << "# Mortgage tests\n\nReal Qt button callbacks with fixed dice (1 + 2). Direct helper tests are labelled separately. Repayment tested at the stored mortgage value; no interest assumed.\n\n";
    auto check=[&](const char* name,bool ok){out<<name<<" — succeeded: "<<(ok?"y":"n")<<"\n\n";};
    {
        Fixture f; f.game.board.Spaces[3].OwnerIndex=0;
        check("Button disabled before rolling",!f.ui.ToggleMortgageButton->isEnabled());
        f.ui.rollDiceButton->click();
        check("Button enabled after rolling, before ending turn",f.ui.ToggleMortgageButton->isEnabled());
        int cash=f.game.Players[0].Money;
        f.ui.ToggleMortgageButton->click();
        check("Button mortgages owned property and pays owner",f.game.board.Spaces[3].isMortgaged && f.game.Players[0].Money==cash+f.game.board.Spaces[3].Mortage);
        f.ui.endTurnButton->click();
        check("Button disabled at start of next player's turn",!f.ui.ToggleMortgageButton->isEnabled());
    }
    {
        Fixture f; f.ui.rollDiceButton->click(); f.ui.buyPropertyButton->click();
        check("Button available immediately after buying property",f.game.board.Spaces[3].OwnerIndex==0 && f.ui.ToggleMortgageButton->isEnabled());
    }
    {
        Fixture f; auto& t=f.game.board.Spaces[3]; t.OwnerIndex=0; f.game.HasRolled=true;
        ToggleMortgage(f.game,f.ui);
        check("Direct helper: mortgage sets flag",t.isMortgaged);
        check("Direct helper: mortgage credits correct amount",f.game.Players[0].Money==1500+t.Mortage);
        check("Displayed balance updates immediately",f.ui.player1->text().contains(QString::number(f.game.Players[0].Money)));
        ToggleMortgage(f.game,f.ui);
        check("Direct helper: unmortgage clears flag",!t.isMortgaged);
        check("Direct helper: unmortgage debits correct amount",f.game.Players[0].Money==1500);
    }
    for(bool mortgaged:{false,true}) {
        Fixture f; auto& t=f.game.board.Spaces[3]; t.OwnerIndex=1; t.isMortgaged=mortgaged; f.game.HasRolled=true;
        ToggleMortgage(f.game,f.ui);
        check(mortgaged?"Direct helper: cannot unmortgage another player's property":"Direct helper: cannot mortgage another player's property",
            t.isMortgaged==mortgaged && f.game.Players[0].Money==1500 && f.game.Players[1].Money==1500);
    }
    for(int position:{3,5,12}) {
        Fixture f; auto& t=f.game.board.Spaces[position]; t.OwnerIndex=1; t.isMortgaged=true;
        MovePlayer(f.game,f.ui,position);
        check(position==3?"No rent on mortgaged street":position==5?"No rent on mortgaged station":"No rent on mortgaged utility",
            f.game.Players[0].Money==1500 && f.game.Players[1].Money==1500);
    }
    {
        Fixture f; auto& t=f.game.board.Spaces[3]; t.OwnerIndex=1;
        MovePlayer(f.game,f.ui,3);
        check("Normal rent still charged on unmortgaged property",f.game.Players[0].Money==1500-t.Rent && f.game.Players[1].Money==1500+t.Rent);
    }
    {
        Fixture f; auto& t=f.game.board.Spaces[3]; t.OwnerIndex=0; t.isMortgaged=true; f.game.Players[0].Money=0; f.game.HasRolled=true;
        ToggleMortgage(f.game,f.ui);
        check("Unaffordable unmortgage leaves cash and mortgage unchanged",t.isMortgaged && f.game.Players[0].Money==0);
    }
    out << "Note: the disabled-button checks pass because the button is always disabled. The unaffordable check passes because the two branches cancel each other's cash changes, not because affordability is validated.\n";
}
