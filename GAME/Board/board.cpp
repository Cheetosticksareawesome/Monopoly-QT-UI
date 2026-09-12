
#include "board.h"

Board CreateBoard()
{
    Board board{};

    BoardSpace Go{
        "Go",
        SpaceType::Go,
    };

    BoardSpace Rest{
        "Rest",
        SpaceType::Rest,
    };



    BoardSpace Oak_st{
        "Oak street",
        SpaceType::Property,
    };

    BoardSpace Pine_st{
        "Pine street",
        SpaceType::Property,
    };

    board.Spaces.push_back(Go);
    board.Spaces.push_back(Oak_st);
    board.Spaces.push_back(Rest);
    board.Spaces.push_back(Pine_st);

    return board;
}