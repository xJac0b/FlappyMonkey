#include "pch.h"
#include "Game.h"
int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    Game game;
    game.run();
    return 0;
}