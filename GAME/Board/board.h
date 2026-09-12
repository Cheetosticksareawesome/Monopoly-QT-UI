#pragma once

#include <string>
#include <vector>

enum class SpaceType
{
    Go,
    Rest,
    Property,
};

struct BoardSpace
{
    std::string Name;
    SpaceType Type;
};

struct Board
{
    std::vector<BoardSpace> Spaces;
};

Board CreateBoard();
