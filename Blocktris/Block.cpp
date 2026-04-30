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

void Block::drawPreviewBlock(sf::RenderWindow& window, const std::vector<sf::Color>& colors, bool isGameOver, int greyRow) const
{
	float cellSize = 460.f / 8.f;  // 4x4 grid scaled to fit preview box
	float gap = 4.f;
	float previewX = static_cast<float>(CELL_SIZE * COLUMNS + 20.f);
	float previewY = 20.f; 

	// find preview window bounds
	int minR = 4, maxR = 0, minC = 4, maxC = 0; 

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				minR = std::min(minR, r);
				maxR = std::max(maxR, r); 
				minC = std::min(minC, c);
				maxC = std::max(maxC, c); 
			}
		}
	}

	// calculate block dimensions in pixels
	float blockWidth = (maxC - minC + 1) * cellSize; 
	float blockHeight = (maxR - minR + 1) * cellSize; 

	// offset to center the block inside the preview box
	float offsetX = previewX + (460.f - blockWidth) / 2.f - minR * cellSize; 
	float offsetY = previewY + (460.f - blockHeight) / 2.f - minC * cellSize;

	sf::RectangleShape cell(sf::Vector2f(cellSize - gap, cellSize - gap));

	if (isGameOver && greyRow == 0)
	{
		cell.setFillColor(sf::Color(75, 75, 75));
	}
	else
	{
		cell.setFillColor(colors[color]);
	}

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				cell.setPosition(sf::Vector2f(offsetX + c * cellSize + gap / 2.f, offsetY + r * cellSize + gap / 2.f));
				window.draw(cell);
			}
		}
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
	int spawnCol = currentPos[1].x;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

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
		--spawnCol;
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

	
	
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r }); 
			}
		}
	}
} 

void TBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

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
		--spawnCol;
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
	


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
}






/* I-Block Code */

void IBlock::constructBlock()
{
	int newSize[4][4] = {
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
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
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	if (rotation % 2 == 0)
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
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
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
		};
		++spawnCol;
		setSize(newSize);
	}
	rotation++;

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
}

void IBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

	if (rotation % 2 == 0)
	{
		int newSize[4][4] = {
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
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
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
		};
		++spawnCol;
		setSize(newSize);
	}
	

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
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
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

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
		++spawnCol;
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
		++spawnCol;
		setSize(newSize);
	}
	rotation++;

	 
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r }); 
			}
		}
	}
}

void LBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

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
		++spawnCol;
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
		++spawnCol;
		setSize(newSize);
	}
	


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
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
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

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
		++spawnCol;
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

	 
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r }); 
			}
		}
	}
}

void JBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

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
		++spawnCol;
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
	


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
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
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

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
		++spawnCol;
		setSize(newSize);
	}
	rotation++;

	
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
}

void ZBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

	if(rotation == -1)
	{
		rotation = 3;
	}

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
		++spawnCol;
		setSize(newSize);
	}
	


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
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
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

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


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r }); 
			}
		}
	}
}

void SBlock::rotateBlockCounter()
{
	int spawnCol = currentPos[1].x - 1;
	int spawnRow = currentPos[1].y;

	for (int r = 0; r < 4; ++r)
	{
		currentPos.pop_back();
	}

	--rotation;

	if (rotation == -1)
	{
		rotation = 3;
	}

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
	


	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (size[r][c] == 1)
			{
				currentPos.push_back({ spawnCol + c, spawnRow + r });
			}
		}
	}
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
	return;
}

void OBlock::rotateBlockCounter()
{
	return;
}