
#include "GameState.h"

void MoveCurrentPlayer(GameState &game, int steps)
{
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    CurrentPlayer.Position = (CurrentPlayer.Position + steps) % game.board.Spaces.size();
}