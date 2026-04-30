#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Window.h"
#include "Block.h"
#include "Game.h"

int main()
{
    // create game object 
    Game blocktris; 

    // run game
    blocktris.runGame(); 

    return 0; 
}