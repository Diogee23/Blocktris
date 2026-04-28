#include "Block.h"

void Block::setSize(int newSize[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			size[i][j] = newSize[i][j];
		}
	}
}

std::vector<sf::Vector2i>& Block::getPosition()
{
	return currentPos;
}

std::vector<Cell> Block::getCells() const
{
	std::vector<Cell> cells;
	// pre allocares 4 cells for every block
	cells.reserve(4);

	for (const sf::Vector2i& pos : currentPos)
	{
		cells.push_back({ pos.y, pos.x });
	}

	return cells;
}

int Block::getColor() const
{
	return color;
}

void Block::drawBlock(sf::RenderWindow& window, const std::vector<sf::Color>& colors) const
{
	float gap = 4.f;
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));

	for (const sf::Vector2i& pos : currentPos)
	{
		cell.setFillColor(colors[color]);
		cell.setPosition(sf::Vector2f(
			static_cast<float>(CELL_SIZE * pos.x + gap / 2.f),
			static_cast<float>(CELL_SIZE * pos.y + gap / 2.f)
		));
		window.draw(cell);
	}
}




/* T-Block Code */

void TBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 1;

	int spawnCol = COLUMNS / 2 - 2; 
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r }); 
			}
		}
	}
}

void TBlock::rotateBlock()
{
	if (rotation % 4 == 0)
	{
		int newSize[4][4] = {
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 1)
	{
		int newSize[4][4] = {
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 2)
	{
		int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}






/* I-Block Code */

void IBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 2;

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void IBlock::rotateBlock()
{
	
	if (rotation % 2 == 0)
	{
		int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}








/* L-Block Code */

void LBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 3; 

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void LBlock::rotateBlock()
{
	if (rotation % 4 == 0)
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 1)
	{
		int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 2)
	{
		int newSize[4][4] = {
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}







/* J-Block Code */

void JBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 4; 

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void JBlock::rotateBlock()
{
	if (rotation % 4 == 0)
	{
		int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 1)
	{
		int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else if (rotation % 4 == 2)
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}






/* Z-Block Code */

void ZBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 5; 

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void ZBlock::rotateBlock()
{
	if (rotation % 2 == 0)
	{
		int newSize[4][4] = {
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}






/* S-Block Code */

void SBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 6; 

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void SBlock::rotateBlock()
{
	if (rotation % 2 == 0)
	{
		int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	else
	{
		int newSize[4][4] = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		};
		setSize(newSize);
	}
	rotation++;
}






/* O-Block Code */

void OBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
	color = 7; 

	int spawnCol = COLUMNS / 2 - 2;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, r });
			}
		}
	}
}

void OBlock::rotateBlock()
{
	int newSize[4][4] = {
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	setSize(newSize);
	rotation = 0;
}