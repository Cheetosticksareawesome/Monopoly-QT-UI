
#include "GameState.h"

void SendToJail(GameState &game)
{
    Player& player = game.Players[game.CurrentPlayerIndex];
    
    player.Position = 10;
    player.InJail = true;
    player.JailTurns = 0;
}