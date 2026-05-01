#include "Block.h"

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

	if (rotation == -1)
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