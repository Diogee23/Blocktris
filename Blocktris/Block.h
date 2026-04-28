#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Window.h"

struct Cell
{
	int row;
	int col;
};

class Block {
public:
	// constructor 
	Block()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				size[i][j] = 0;
			}
		}

		rotation = 0;
		color = -1;
	}

	// destructor 
	~Block() = default;

	// setters 
	void setSize(int newSize[4][4]);
	void setRotation(int NewRotation) { rotation = NewRotation; }

	// getter 
	sf::Vector2i getPosition() const;
	std::vector<Cell> getCells() const; 
	int getColor() const; 

	// virtual constructor function -- to be defined in each specific block class 
	virtual void constructBlock() = 0;

	// virtual rotation function -- to be defined in each specific block class 
	virtual void rotateBlock() = 0;

	//makes the blocks fall
	bool moveDown(const std::vector<std::vector<int>>& indexMatrix);

protected:
	// attributes
	int size[4][4];
	int rotation;
	int color; 
	std::vector<sf::Vector2i> currentPos;
};

class TBlock : public Block {
public:
	// constructor -- calls construct block function 
	TBlock()
	{
		constructBlock();
	}

	// destructor 
	~TBlock() = default; 

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};

class IBlock : public Block {
public:
	// constructor -- calls construct block function 
	IBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~IBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};

class LBlock : public Block {
public:
	// constructor -- calls construct block function
	LBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~LBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};

class JBlock : public Block {
public:
	// constructor -- calls construct block function 
	JBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~JBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block
	void rotateBlock() override;
private:

};

class ZBlock : public Block {
public:
	// constructor -- calls construct block function 
	ZBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~ZBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};

class SBlock : public Block {
public:
	// constructor -- calls construct block function 
	SBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~SBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};

class OBlock : public Block {
public:
	// constructor -- calls construct block function 
	OBlock() 
	{ 
		constructBlock(); 
	}

	// destructor 
	~OBlock() = default;

	// creates the block 
	void constructBlock() override;

	// rotates the block 
	void rotateBlock() override;
private:

};