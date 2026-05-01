#pragma once

#include "Block.h"

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