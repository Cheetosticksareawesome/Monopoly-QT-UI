#include "board.h"
#include "DrawableCards.h"
#include "ui_MainUI.h"
#include "logger-manager.h"

#include <QLabel>

Board CreateBoard()
{
    Board board{};
    
    //         Variable           Name                 Type                         Price  Rent  Mortage OwnerIndex
    BoardSpace Rest             { "Rest",              SpaceType::Rest,                0,    0,       0,         -1 };

    BoardSpace Go               { "GO",                SpaceType::Go,                  0,    0,       0,         -1 };
    BoardSpace Oak_st           { "Oak Street",        SpaceType::Property,           60,    2,      30,         -1 };
    BoardSpace CommunityChest   { "Community Chest",   SpaceType::Community_Chest,     0,    0,       0,         -1 };
    BoardSpace Pine_st          { "Pine Street",       SpaceType::Property,           60,    4,      30,         -1 };
    BoardSpace IncomeTax        { "Income Tax",        SpaceType::IncomeTax,           0,    0,       0,         -1 };
    BoardSpace SouthStation     { "South Station",     SpaceType::TrainStation,      200,   25,     100,         -1 };
    BoardSpace Birch_st         { "Birch Street",      SpaceType::Property,          100,    6,      50,         -1 };
    BoardSpace Chance           { "Chance",            SpaceType::Chance,              0,    0,       0,         -1 };
    BoardSpace Maple_st         { "Maple Street",      SpaceType::Property,          100,    6,      50,         -1 };
    BoardSpace Cedar_st         { "Cedar Street",      SpaceType::Property,          120,    8,      60,         -1 };
    BoardSpace Jail             { "JAIL / VISITING",   SpaceType::Jail,                0,    0,       0,         -1 };
    BoardSpace Rose_st          { "Rose Street",       SpaceType::Property,          140,   10,      70,         -1 };
    BoardSpace ElectricCompany  { "Electric Company",  SpaceType::Utility,           150,   28,      75,         -1 };
    BoardSpace Tulip_st         { "Tulip Street",      SpaceType::Property,          140,   10,      70,         -1 };
    BoardSpace Lily_st          { "Lily Street",       SpaceType::Property,          160,   12,      80,         -1 };
    BoardSpace WestStation      { "West Station",      SpaceType::TrainStation,      200,   25,     100,         -1 };
    BoardSpace Orange_st        { "Orange Street",     SpaceType::Property,          180,   14,      90,         -1 };
    BoardSpace Peach_st         { "Peach Street",      SpaceType::Property,          180,   14,      90,         -1 };
    BoardSpace Apricot_st       { "Apricot Street",    SpaceType::Property,          200,   16,     100,         -1 };
    BoardSpace FreeParking      { "FREE PARKING",      SpaceType::Free_Parking,        0,    0,       0,         -1 };
    BoardSpace Ruby_st          { "Ruby Street",       SpaceType::Property,          220,   18,     110,         -1 };
    BoardSpace Scarlet_st       { "Scarlet Street",    SpaceType::Property,          220,   18,     110,         -1 };
    BoardSpace Crimson_st       { "Crimson Street",    SpaceType::Property,          240,   20,     120,         -1 };
    BoardSpace NorthStation     { "North Station",     SpaceType::TrainStation,      200,   25,     100,         -1 };
    BoardSpace Sunflower_st     { "Sunflower Street",  SpaceType::Property,          260,   22,     130,         -1 };
    BoardSpace Daffodil_st      { "Daffodil Street",   SpaceType::Property,          260,   22,     130,         -1 };
    BoardSpace WaterWorks       { "Water Works",       SpaceType::Utility,           150,   28,      75,         -1 };
    BoardSpace Marigold_st      { "Marigold Street",   SpaceType::Property,          280,   24,     140,         -1 };
    BoardSpace GoToJail         { "GO TO JAIL",        SpaceType::GoToJail,            0,    0,       0,         -1 };
    BoardSpace Forest_st        { "Forest Street",     SpaceType::Property,          300,   26,     150,         -1 };
    BoardSpace Willow_st        { "Willow Street",     SpaceType::Property,          300,   26,     150,         -1 };
    BoardSpace Meadow_st        { "Meadow Street",     SpaceType::Property,          320,   28,     160,         -1 };
    BoardSpace EastStation      { "East Station",      SpaceType::TrainStation,      200,   25,     100,         -1 };
    BoardSpace Ocean_ave        { "Ocean Avenue",      SpaceType::Property,          350,   35,     175,         -1 };
    BoardSpace LuxuryTax        { "Luxury Tax",        SpaceType::Luxury_Tax,          0,    0,       0,         -1 };
    BoardSpace Royal_ave        { "Royal Avenue",      SpaceType::Property,          400,   50,     200,         -1 };

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