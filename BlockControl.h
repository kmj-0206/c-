#pragma once
#include "TetrisBlock.h"

class Board;

class BlockControl
{
private:
    TetrisBlock* curControlBlock;
    const Board* curBoard;

public:
    BlockControl() = delete;
    BlockControl(const Board& board);
    ~BlockControl();

    bool move(MoveCommand cmd);
    void dropFull();
    bool canMoveTo(const BlockState& state) const;

    TetrisBlock* getCurrentBlock() { return curControlBlock; }
    void setCurrentBlock(TetrisBlock& block) { curControlBlock = &block; }
};
