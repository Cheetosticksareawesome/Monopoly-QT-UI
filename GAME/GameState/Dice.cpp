
#include <random>

#include "Dice.h"

int RollDie()
{
    static std::mt19937 Generator{std::random_device()()};

    std::uniform_int_distribution<int> die{ 1, 6 };

    return die(Generator);
}

int RollDice()
{
    int Die_1{RollDie()};
    int Die_2{RollDie()};

    return Die_1 + Die_2;
}