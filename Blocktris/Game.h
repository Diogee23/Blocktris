#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <memory>
#include <chrono>
#include "Window.h"
#include "Block.h"
#include "Grid.h"
#include "Character.h"
#include "CharAnimation.h"

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

	Character Andy;

	CharAnimation upsetAndy;
	bool andyAnimationStarted = false;

	CharAnimation angeredAndy;
	bool andyAnimation2Started = false;

	void resetGame(std::unique_ptr<Block>& activeBlock, std::unique_ptr<Block>& nextBlock, Grid& grid, int& lines_cleared, int& level, int& fallTimer, int& currentFallSpd);

private:
    // attributes 
    Grid grid;

	// Andy Fight
	bool fightingAndy = false;
	int bossHP = 20;

    // creates new random block 
    std::unique_ptr<Block> spawnBlock();
};