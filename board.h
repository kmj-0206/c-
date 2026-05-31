#pragma once
#include "TetrisBlock.h"
#include <set> 

struct ClearResult {
    int fullLines;
    std::set<int> removedRows; // int에서 set으로 변경 (애니메이션 처리를 위함)
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

    // 기존 clearFullLines() 대신 로직을 분리
    ClearResult checkClearLines();
    void removeLines(const std::set<int>& rowsToRemove);

    char getCell(int y, int x) const;

    int getBoardWidth() const { return 14; }
    int getBoardHeight() const { return 21; }

    char getBoardValue(int y, int x) const { return cells[y][x]; }
};