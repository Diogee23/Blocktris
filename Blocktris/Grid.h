#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Window.h"

class Grid {
public:
	// constructor 
	Grid();

	// move Block functions -- allow the block to move down, left, and right
	bool moveBlockDown(Block& block);
	bool moveBlockLeft(Block& block); 
	bool moveBlockRight(Block& block);

	// code for the hard drop
	std::vector<sf::Vector2i> getGhost(Block& block);
	void hardDrop(Block& block);

	// if the block is in a bad position, put it in a good slot and place it
	void bounceBlock(Block& block);

	// rotate Block functions - rotate blocks either clockwise or counter-clockwise
	void rotateBlock(Block& block);
	void rotateBlockCounter(Block& block);

	// checks if the block is in a valid position 
	bool isValidPosition(const Block& block) const; //?

	// stores the block's position in the grid 
	void lockBlock(const Block& block);

	// clears line once complete and moves rows accordingly 
	int clearLine();

	// helper function for clear line, checks if the row is full 
	bool isRowFull(int row); 

	// returns rows that are full
	std::vector<int> getFullRows();

	// draws the cells in the grid 
	void draw(sf::RenderWindow& window, const std::vector<sf::Color>& colors, bool isGameOver, int greyRow) const;

	// checks if a blocks block has touched the top of the grid
	bool isTopReached() const;

private:
	// attribute 
	int grid[ROWS][COLUMNS]; // game grid 

	// private functions 

	// checks if the cell is inside the grid 
	bool isInside(int row, int col) const;

	// checks if the cell is empty 
	bool isEmpty(int row, int col) const;
};