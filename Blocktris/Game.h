#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <memory>
#include <chrono>
#include "Window.h"
#include "Block.h"
#include "Grid.h"

class Game 
{
public:
    // constructor 
    Game() = default;

    // destructor 
    ~Game() = default;

    // runs the main Blocktris game 
    void runGame();

	bool isGameOver = false;

	void checkGameOver(const Grid& grid, const Block& block);
    // starts below the board
	int greyRow = ROWS;   
	int greyTimer = 0;

private:
    // attributes 
    Grid grid;

    // creates new random block 
    std::unique_ptr<Block> spawnBlock();
};