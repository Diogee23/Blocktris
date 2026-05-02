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

    Character Andy;
    Character AndyPlaceholder;

    CharAnimation upsetAndy;
    bool andyAnimationStarted = false;

    CharAnimation angeredAndy;
    bool andyAnimation2Started = false;

    // constructor 
    Game() = default;

    // destructor 
    ~Game() = default;

    // runs the main Blocktris game 
    void runGame();

    void checkGameOver(const Grid& grid, const Block& block);

    void resetGame(std::unique_ptr<Block>& activeBlock, std::unique_ptr<Block>& nextBlock, Grid& grid, int& lines_cleared, int& level, int& fallTimer, int& currentFallSpd);

    bool isGameOver = false;

    // starts below the board
    int greyRow = ROWS;
    int greyTimer = 0;

private:

    // attributes 
    Grid grid;

    // creates new random block 
    std::unique_ptr<Block> spawnBlock();

    //for blask screen at end 
    int fadeAlpha = 0;
    bool startFade = false;
};
