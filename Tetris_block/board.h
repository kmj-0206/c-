#pragma once
#include "TetrisBlock.h"
class board
{
private: 
	char cells[21][14];

public:
	void init();

	bool isCollision(const TetrisBlock& block);
	void merge(const TetrisBlock& block);
	int clearFullLines(int& score, int& lines, int level);

	char getCell(int y, int x) const;
};

