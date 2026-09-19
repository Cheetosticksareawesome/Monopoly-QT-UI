#pragma once

#include <string>
#include <vector>

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
    int Mortage{Price / 2};
    int OwnerIndex{-1};
};

struct Board
{
    std::vector<BoardSpace> Spaces;
    int FreeParkingMoney{0};
};

Board CreateBoard();
