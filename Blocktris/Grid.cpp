#include "Grid.h"

Grid::Grid()
{
	//loops through all rows
	for(int i = 0; i < ROWS; ++i)
	{
		//loops through all cols
		for(int j = 0; j < COLUMNS; ++j)
		{
			//sets/ensures they are all to 0 on construction 
			grid[i][j] = 0;
		}
	}
}

int Grid::clearLine()
{
    int linesCleared = 0;

    // Start from the bottom row and work upward
    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (isRowFull(row))
        {
            // Shift all rows above down by one
            for (int row2 = row; row2 > 0; --row2)
            {
                for (int col = 0; col < COLUMNS; ++col)
                {
                    grid[row2][col] = grid[row2 - 1][col];
                }
            }

            // Clear the top row
            for (int col = 0; col < COLUMNS; ++col)
            {
                grid[0][col] = 0;
            }

            ++linesCleared;
            ++row; // Recheck this row index since everything shifted down
        }
    }

    return linesCleared; 
}

bool Grid::isRowFull(int row)
{
    for (int col = 0; col < COLUMNS; ++col)
    {
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true; 
}

bool Grid::isValidPosition(const Block& block) const 
{
	for (const Cell& cell : block.getCells())
    {
        int r = cell.row;
        int c = cell.col;


    }
	return true;
}

void Grid::lockBlock(const Block& block)
{


}

void Grid::draw(sf::RenderWindow& window) const
{

}

bool Grid::isInside(int row, int col) const
{

}

bool Grid::isEmpty(int row, int col) const
{

}

void Grid::createBlock()
{

}