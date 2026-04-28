#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "Window.h"
#include "Block.h"
#include "Grid.h"

class Game 
{
public:
    // constructor 
    Game() 
    {
        // nothing to do here
    }

    // destructor 
    ~Game() 
    {
        // nothing to do here 
    }

    // runs the main Blocktris game 
    void runGame();

private:
    std::unique_ptr<Block> spawnBlock();
};
