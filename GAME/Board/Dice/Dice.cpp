
#include <random>

#include "Dice.h"

int RollDie()
{
    static std::mt19937 Generator{std::random_device()()};

    std::uniform_int_distribution<int> die{ 1, 6 };

    return die(Generator);
}

DiceRoll RollDice()
{
    return {RollDie(), RollDie()};
}