
#include "GameState.h"

void SendToJail(Player& player)
{
    player.Position = 10;
    player.InJail = true;
    player.Money -= 25;
    player.JailTurns = 0;
    player.DoubleDiceCount = 0;
}