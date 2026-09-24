
#include "Player.h"
#include "GameState.h"

std::string PlayerIndexToName(GameState& game, int& playerIndex)
{
    if(playerIndex == -1)
        return "Unowned";
    if(playerIndex < 0 || playerIndex >= game.Players.size())
        return "Unknown player";
    return game.Players[playerIndex].Name;
}
