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

bool Grid::moveBlockDown(Block& block)
{
    for (const Cell& cell : block.getCells())
    {
        if (cell.row + 1 >= ROWS || grid[cell.row + 1][cell.col] != 0)
        {
            return false;
        }
    }

    for (sf::Vector2i& pos : block.getPosition())
    {
        ++pos.y;
    }

    return true;
}

bool Grid::moveBlockLeft(Block& block)
{
    for (const Cell& cell : block.getCells())
    {
        if (grid[cell.row][cell.col - 1] != 0)
        {
            return false;
        }
    }

    for (sf::Vector2i& pos : block.getPosition())
    {
        --pos.x;
		pos.x < 0 ? pos.x = pos.x + 10 : pos.x = pos.x;
		pos.x > 10 ? pos.x = 10 - pos.x : pos.x = pos.x;
    }

    return true;
}

bool Grid::moveBlockRight(Block& block)
{
    for (const Cell& cell : block.getCells())
    {
        if (grid[cell.row][cell.col + 1] != 0)
        {
            return false;
        }
    }

    for (sf::Vector2i& pos : block.getPosition())
    {
        ++pos.x;
		pos.x < 0 ? pos.x = pos.x + 10 : pos.x = pos.x;
		pos.x > 10 ? pos.x = 10 - pos.x : pos.x = pos.x;
    }

    return true;
}

std::vector<sf::Vector2i> Grid::getGhost(Block& block)
{
	// moving the tetromino down until it hits something then returning its position
	bool keep_falling = 1;

	unsigned char total_movement = 0;

	std::vector<sf::Vector2i> ghostBlock = block.getPosition();

	while (keep_falling == 1)
	{
		for (const Cell& cells : block.getCells())
		{
			if (total_movement + cells.row + 1 >= ROWS||
				(total_movement + cells.row + 1 >= 0 &&
					grid[cells.row + total_movement + 1][cells.col] != 0))
			{
				keep_falling = 0;
				break;
			}
		}

        if (keep_falling == 1)
        {
            ++total_movement;
        }
	}

	for (sf::Vector2i& pos : ghostBlock)
	{
		 pos.y += total_movement;
	}

	return ghostBlock;
}


void Grid::hardDrop(Block& block)
{
    std::vector<sf::Vector2i> ghost = getGhost(block);
    block.setPosition(ghost);
}



void Grid::rotateBlock(Block& block)
{
    block.rotateBlock();
}

void Grid::rotateBlockCounter(Block& block)
{
	block.rotateBlockCounter();
}

void Grid::bounceBlock(Block& block)
{
    // essentially the same as hard drop, but it checks above the block as well

bool keep_falling = 1;

unsigned char total_movement = 0;

// Only difference from the getGhost function is that we move the ghost block far above the grid to avoid clipping issues
for (sf::Vector2i& pos : block.getPosition())
{
    pos.y = pos.y - 19;
}

std::vector<sf::Vector2i> ghostBlock = block.getPosition();

while (keep_falling == 1)
{
    for (const Cell& cells : block.getCells())
    {
        if (total_movement + cells.row + 1 >= ROWS ||
            (total_movement + cells.row + 1 >= 0 &&
                grid[cells.row + total_movement + 1][cells.col] != 0))
        {
            keep_falling = 0;
            break;
        }
    }

    if (keep_falling == 1)
    {
        ++total_movement;
    }
}

for (sf::Vector2i& pos : ghostBlock)
{
    pos.y += total_movement;
}

block.setPosition(ghostBlock);


// If the block is still above the grid, smush it flat on top row so it can actually be placed and the game can end
for (sf::Vector2i& pos : block.getPosition())
{
    if (pos.y < 0)
    {
        pos.y = 0;
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

std::vector<int> Grid::getFullRows()
{
    std::vector<int> fullRows;

    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (isRowFull(row))
        {
            fullRows.push_back(row); 
        }
    }

    return fullRows;
}

bool Grid::isValidPosition(const Block& block) const 
{
	for (const Cell& cell : block.getCells())
    {
        int r = cell.row;
        int c = cell.col;

        if (isInside(r, c) == false)
        {
            return false; 
        }

        if (isEmpty(r, c) == false)
        {
            return false; 
        }
    }
	return true;
}

void Grid::lockBlock(const Block& block)
{
    for (const Cell& cell : block.getCells())
    {
        int r = cell.row;
        int c = cell.col;

        grid[r][c] = block.getColor(); 
    }
}

void Grid::draw(sf::RenderWindow& window, const std::vector<sf::Color>& colors, bool isGameOver, int greyRow) const
{
    float gap = 4.f; 

    for (int row = ROWS - 1; row >= 0; --row)
    {
        for (int col = COLUMNS - 1; col >= 0; --col)
        {
            if (grid[row][col] != 0)
            {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));
                // grey out blocks if the game is over

                if (isGameOver)
                {
                    if (row >= greyRow)
                    {
                        cell.setFillColor(sf::Color(75, 75, 75));
                    }
                    else
                    {
                        cell.setFillColor(colors[grid[row][col]]);
                    }
                }
                else
                {
                    cell.setFillColor(colors[grid[row][col]]);
                }
                cell.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * col + gap / 2.f), static_cast<float>(CELL_SIZE * row + gap / 2.f)));
                window.draw(cell);
            }
        }
    }
	
}

bool Grid::isTopReached() const
{
	// checks if ANY column in the top row is filled
	for (int i = 0; i < COLUMNS; ++i)
    {
		if (grid[0][i] != 0) 
        {
			return true;
		}
	}
	return false;
}



bool Grid::isInside(int row, int col) const
{
    if (row >= 0 && row < ROWS)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

bool Grid::isEmpty(int row, int col) const
{
    if (grid[row][col] == 0)
    {
        return true;
    }
    else
    {
        return false; 
    }
}
