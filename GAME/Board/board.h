#pragma once

#include <string>
#include <vector>

#include "DrawableCards.h"

enum class SpaceType
{
    Go,
    Rest,
    Property,
    Chance,
    Jail,
    GoToJail,
    IncomeTax,
    TrainStation,
    Free_Parking,
    Utility,
    Luxury_Tax,
    Community_Chest,
};

struct BoardSpace
{
    std::string Name;
    SpaceType Type;
    int Price{0};
    int Rent{0};
    bool isMortgaged{false};
    int Mortage{Price / 2};
    int OwnerIndex{-1};
    std::string ColorGroup;
    int HouseCount{0};
    int HousePrice{0};
};

struct Board
{
    std::vector<BoardSpace> Spaces;
    int FreeParkingMoney{0};
};

Board CreateBoard();

std::string ToStdStringSpaceType(SpaceType type);
void ToggleMortgage(GameState &game, Ui::MainWindow &ui);
bool DoubleRentCheck(GameState &game, BoardSpace &current);
void buyHouse(GameState &game, Ui::MainWindow &ui);