#pragma once
#include "TetrisBlock.h"

class Board
{
private:
    char cells[21][14];

public:
    void init();

    bool isCollision(const TetrisBlock& block);
    void merge(const TetrisBlock& block);

    int clearFullLines(int& score, int& lines, int level);

    char getCell(int y, int x) const;

    int getBoardWidth() const {
        return 14;
    }

    int getBoardHeight() const {
        return 21;
    }

    char getBoardValue(int y, int x) const {
        return cells[y][x];
    }
};