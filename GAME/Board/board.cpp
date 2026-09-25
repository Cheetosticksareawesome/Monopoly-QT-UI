#include "board.h"
#include "DrawableCards.h"
#include "ui_MainUI.h"
#include "logger-manager.h"
#include "GameState.h"

#include <QLabel>

Board CreateBoard()
{
    Board board{};
    
    //         Variable           Name                 Type                         Price  Rent  isMortgaged  Mortage OwnerIndex ColorGroup HouseCount
    BoardSpace Rest             { "Rest",              SpaceType::Rest,                0,    0,    false,       0,         -1, "", 0 };

    BoardSpace Go               { "GO",                SpaceType::Go,                  0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Oak_st           { "Oak Street",        SpaceType::Property,           60,    2,    false,      30,         -1, "Brown", 0 };
    BoardSpace CommunityChest   { "Community Chest",   SpaceType::Community_Chest,     0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Pine_st          { "Pine Street",       SpaceType::Property,           60,    4,    false,      30,         -1, "Brown", 0 };
    BoardSpace IncomeTax        { "Income Tax",        SpaceType::IncomeTax,           0,    0,    false,       0,         -1, "", 0 };
    BoardSpace SouthStation     { "South Station",     SpaceType::TrainStation,      200,   25,    false,     100,         -1, "", 0 };
    BoardSpace Birch_st         { "Birch Street",      SpaceType::Property,          100,    6,    false,      50,         -1, "LightBlue", 0 };
    BoardSpace Chance           { "Chance",            SpaceType::Chance,              0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Maple_st         { "Maple Street",      SpaceType::Property,          100,    6,    false,      50,         -1, "LightBlue", 0 };
    BoardSpace Cedar_st         { "Cedar Street",      SpaceType::Property,          120,    8,    false,      60,         -1, "LightBlue", 0 };
    BoardSpace Jail             { "JAIL / VISITING",   SpaceType::Jail,                0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Rose_st          { "Rose Street",       SpaceType::Property,          140,   10,    false,      70,         -1, "Pink", 0 };
    BoardSpace ElectricCompany  { "Electric Company",  SpaceType::Utility,           150,   28,    false,      75,         -1, "", 0 };
    BoardSpace Tulip_st         { "Tulip Street",      SpaceType::Property,          140,   10,    false,      70,         -1, "Pink", 0 };
    BoardSpace Lily_st          { "Lily Street",       SpaceType::Property,          160,   12,    false,      80,         -1, "Pink", 0 };
    BoardSpace WestStation      { "West Station",      SpaceType::TrainStation,      200,   25,    false,     100,         -1, "", 0 };
    BoardSpace Orange_st        { "Orange Street",     SpaceType::Property,          180,   14,    false,      90,         -1, "Orange", 0 };
    BoardSpace Peach_st         { "Peach Street",      SpaceType::Property,          180,   14,    false,      90,         -1, "Orange", 0 };
    BoardSpace Apricot_st       { "Apricot Street",    SpaceType::Property,          200,   16,    false,     100,         -1, "Orange", 0 };
    BoardSpace FreeParking      { "FREE PARKING",      SpaceType::Free_Parking,        0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Ruby_st          { "Ruby Street",       SpaceType::Property,          220,   18,    false,     110,         -1, "Red", 0 };
    BoardSpace Scarlet_st       { "Scarlet Street",    SpaceType::Property,          220,   18,    false,     110,         -1, "Red", 0 };
    BoardSpace Crimson_st       { "Crimson Street",    SpaceType::Property,          240,   20,    false,     120,         -1, "Red", 0 };
    BoardSpace NorthStation     { "North Station",     SpaceType::TrainStation,      200,   25,    false,     100,         -1, "", 0 };
    BoardSpace Sunflower_st     { "Sunflower Street",  SpaceType::Property,          260,   22,    false,     130,         -1, "Yellow", 0 };
    BoardSpace Daffodil_st      { "Daffodil Street",   SpaceType::Property,          260,   22,    false,     130,         -1, "Yellow", 0 };
    BoardSpace WaterWorks       { "Water Works",       SpaceType::Utility,           150,   28,    false,      75,         -1, "", 0 };
    BoardSpace Marigold_st      { "Marigold Street",   SpaceType::Property,          280,   24,    false,     140,         -1, "Yellow", 0 };
    BoardSpace GoToJail         { "GO TO JAIL",        SpaceType::GoToJail,            0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Forest_st        { "Forest Street",     SpaceType::Property,          300,   26,    false,     150,         -1, "Green", 0 };
    BoardSpace Willow_st        { "Willow Street",     SpaceType::Property,          300,   26,    false,     150,         -1, "Green", 0 };
    BoardSpace Meadow_st        { "Meadow Street",     SpaceType::Property,          320,   28,    false,     160,         -1, "Green", 0 };
    BoardSpace EastStation      { "East Station",      SpaceType::TrainStation,      200,   25,    false,     100,         -1, "", 0 };
    BoardSpace Ocean_ave        { "Ocean Avenue",      SpaceType::Property,          350,   35,    false,     175,         -1, "DarkBlue", 0 };
    BoardSpace LuxuryTax        { "Luxury Tax",        SpaceType::Luxury_Tax,          0,    0,    false,       0,         -1, "", 0 };
    BoardSpace Royal_ave        { "Royal Avenue",      SpaceType::Property,          400,   50,    false,     200,         -1, "DarkBlue", 0 };

    board.Spaces.resize(40, Rest);
    board.Spaces[0] = Go;
    board.Spaces[1] = Oak_st;
    board.Spaces[2] = CommunityChest;
    board.Spaces[3] = Pine_st;
    board.Spaces[4] = IncomeTax;
    board.Spaces[5] = SouthStation;
    board.Spaces[6] = Birch_st;
    board.Spaces[7] = Chance;
    board.Spaces[8] = Maple_st;
    board.Spaces[9] = Cedar_st;
    board.Spaces[10] = Jail;
    board.Spaces[11] = Rose_st;
    board.Spaces[12] = ElectricCompany;
    board.Spaces[13] = Tulip_st;
    board.Spaces[14] = Lily_st;
    board.Spaces[15] = WestStation;
    board.Spaces[16] = Orange_st;
    board.Spaces[17] = Peach_st;
    board.Spaces[18] = CommunityChest;
    board.Spaces[19] = Apricot_st;
    board.Spaces[20] = FreeParking;
    board.Spaces[21] = Ruby_st;
    board.Spaces[22] = Chance;
    board.Spaces[23] = Scarlet_st;
    board.Spaces[24] = Crimson_st;
    board.Spaces[25] = NorthStation;
    board.Spaces[26] = Sunflower_st;
    board.Spaces[27] = Daffodil_st;
    board.Spaces[28] = WaterWorks;
    board.Spaces[29] = Marigold_st;
    board.Spaces[30] = GoToJail;
    board.Spaces[31] = Forest_st;
    board.Spaces[32] = Willow_st;
    board.Spaces[33] = CommunityChest;
    board.Spaces[34] = Meadow_st;
    board.Spaces[35] = EastStation;
    board.Spaces[36] = Chance;
    board.Spaces[37] = Ocean_ave;
    board.Spaces[38] = LuxuryTax;
    board.Spaces[39] = Royal_ave;

    return board;
}

std::string ToStdStringSpaceType(SpaceType type)
{
    switch (type)
    {
        case SpaceType::Chance:
            return "Chance";
        break;
        case SpaceType::Community_Chest:
            return "Community Chest";
        break;
        case SpaceType::Free_Parking:
            return "Free Parking";
        break;
        case SpaceType::Go:
            return "Go";
        break;
        case SpaceType::GoToJail:
            return "Go To Jail";
        break;
        case SpaceType::IncomeTax:
            return "Income Tax";
        break;
        case SpaceType::Jail:
            return "Jail";
        break;
        case SpaceType::Luxury_Tax:
            return "Luxury Tax";
        break;
        case SpaceType::Property:
            return "Property";
        break;
        case SpaceType::Rest:
            return "Rest";
        break;
        case SpaceType::TrainStation:
            return "Trainstation";
        break;
        case SpaceType::Utility:
            return "Utility";
        break;

        default:
            LogLineAppend("Conversion Error for SpaceType!");
        return "Conversion Error";
    }
}

void ToggleMortgage(GameState& game, Ui::MainWindow& ui)
{
    BoardSpace& target = game.board.Spaces[ui.MortgageField->text().toInt()];
    if(target.OwnerIndex != -1)
    {
        Player& Owner = game.Players[target.OwnerIndex];
        QLabel *mortgageLabel = ui.centralwidget->findChild<QLabel *>("mortgageLabel" + ui.MortgageField->text());

        if(target.OwnerIndex == game.CurrentPlayerIndex){

            if(target.isMortgaged)
            {
                target.isMortgaged = false;
                Owner.Money -= target.Mortage;
                mortgageLabel->hide();
                return;
            }
            if(!target.isMortgaged)
            {
                target.isMortgaged = true;
                Owner.Money += target.Mortage;
                mortgageLabel->show();
                return;
            }
        }
    }
}

bool DoubleRentCheck(GameState& game, BoardSpace& current)
{
    
    for(BoardSpace space : game.board.Spaces)
    {
        if(space.ColorGroup == current.ColorGroup && space.OwnerIndex != current.OwnerIndex)
        {
            return false;
        }
    }
    return true;
}

void buyHouse(GameState& game)
{
    
}