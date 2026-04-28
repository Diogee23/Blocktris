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
        if (cell.col - 1 < 0 || grid[cell.row][cell.col - 1] != 0)
        {
            return false;
        }
    }

    for (sf::Vector2i& pos : block.getPosition())
    {
        --pos.x;
    }

    return true;
}

bool Grid::moveBlockRight(Block& block)
{
    for (const Cell& cell : block.getCells())
    {
        if (cell.col + 1 >= COLUMNS || grid[cell.row][cell.col + 1] != 0)
        {
            return false;
        }
    }

    for (sf::Vector2i& pos : block.getPosition())
    {
        ++pos.x;
    }

    return true;
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

void Grid::draw(sf::RenderWindow& window, const std::vector<sf::Color>& colors) const
{
    float gap = 4.f; 

    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            if (grid[row][col] != 0)
            {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));
                cell.setFillColor(colors[grid[row][col]]);
                cell.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * col + gap / 2.f), static_cast<float>(CELL_SIZE * row + gap / 2.f)));
                window.draw(cell);
            }
        }
    }
}

bool Grid::isInside(int row, int col) const
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS)
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


void Grid::createBlock()
{
    int randNum = rand() % 7;

    switch(randNum)
    {
	    case 0:
            //code new TBlock();
		    break;
	    case 1:
            //code new IBlock();
		    break;
	    case 2:
            //code new LBlock();
            break;
        case 3:
            //code new JBlock();
            break;
		case 4:
			//code new ZBlock();
			break;
		case 5:
			//code new SBlock();
			break;
		case 6:
			//code new OBlock();
			break;

    }
    
}