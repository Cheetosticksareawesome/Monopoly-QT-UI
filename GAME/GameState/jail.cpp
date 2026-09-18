
#include "GameState.h"

void SendToJail(Player& player)
{
    player.Position = 10;
    player.InJail = true;
    player.JailTurns = 0;
    player.DoubleDiceCount = 0;
}