#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Window.h"

class Grid {
public:
	// constructor 
	Grid();

	void createBlock();

	bool isValidPosition(const Block& block) const; //?

	void lockBlock(const Block& block);

	// clears line once complete and moves rows accordingly 
	void clearLine();
	// helper function for clear line, checks if the row is full 
	bool isRowFull(int row); 

	void draw(sf::RenderWindow& window) const;

private:
	int grid[ROWS][COLUMNS];

	bool isInside(int row, int col) const;
	bool isEmpty(int row, int col) const;
};