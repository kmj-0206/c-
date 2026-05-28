#pragma once
#include "TetrisBlock.h"

struct ClearResult {
    int fullLines;
    int removedRows;
    bool itemA;
    bool itemB;
    bool itemC;
};

class Board
{
private:
    char cells[21][14];

public:
    void init();

    bool isCollision(const BlockState& state, int shape) const;
    void merge(const TetrisBlock& block);

    ClearResult clearFullLines();

    char getCell(int y, int x) const;

    int getBoardWidth() const { return 14; }
    int getBoardHeight() const { return 21; }

    char getBoardValue(int y, int x) const { return cells[y][x]; }
};
