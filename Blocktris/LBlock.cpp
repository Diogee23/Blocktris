#include "Block.h"

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