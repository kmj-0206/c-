<<<<<<< HEAD
#pragma once
#include "TetrisBlock.h"

struct ClearResult {
    int fullLines;
    int removedRows;
    bool itemA;
    bool itemB;
    bool itemC;
};

=======
﻿#pragma once
#include "TetrisBlock.h"

>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
class Board
{
private:
    char cells[21][14];

public:
    void init();

<<<<<<< HEAD
    bool isCollision(const BlockState& state, int shape) const;
    void merge(const TetrisBlock& block);

    ClearResult clearFullLines();

    char getCell(int y, int x) const;

    int getBoardWidth() const { return 14; }
    int getBoardHeight() const { return 21; }

    char getBoardValue(int y, int x) const { return cells[y][x]; }
};
=======
    bool isCollision(const BlockState& state,int shape) const;
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
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
