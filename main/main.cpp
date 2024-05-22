#include <iostream>
#include "public/GameLoop.h"
#include "public/DataContainer.h"

int main(int argc, char* argv[])
{
    GameLoop gameLoop;

    // Triggers some related code to get and set the game data
    // Creates the class that contains all game data
    gameLoop.ReceiveData();

    // Initializes the objects created by the gameloop class.
    gameLoop.Start();
    // Each frame starts a block of code that runs
    gameLoop.Run();
    
    return 0;
}
