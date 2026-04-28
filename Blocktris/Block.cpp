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

std::vector<sf::Vector2i> Block::getPosition() const
{
	return currentPos;
}

std::vector<Cell> Block::getCells() const
{
	std::vector<Cell> cells;
	// pre allocares 4 cells for every block
	cells.reserve(4);

	return cells;
}


int Block::getColor() const
{
	return color;
}

bool Block::moveDown(const std::vector<std::vector<int>>& indexMatrix) 
{
	for (sf::Vector2i& block : currentPos)
	{
		if (ROWS == 1 + block.y || indexMatrix[block.x][1 + block.y] > 0)
		{
			return false;
		}
	}

	for (sf::Vector2i& block : currentPos)
	{
		++block.y;
	}
	
	return true;
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
	rotation = 6;
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