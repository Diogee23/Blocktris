#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Window.h"
#include "Block.h"
#include "Game.h"
#include "TestCases.h"

int main()
{
    // test cases object
    TestCases tests; 

    // run all test cases 
    tests.runAll(); 

    // create game object 
    Game blocktris; 

    // run game
    blocktris.runGame(); 

    return 0; 
}