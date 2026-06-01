#pragma once
#include "TetrisBlock.h"

class Board;

class BlockControl
{
private:
    TetrisBlock* curControlBlock; // 현재 조작 중인 블록. 소유하지 않고 참조만 한다.
    const Board* curBoard;        // 충돌 검사용 보드. 소유하지 않는다.

public:
    BlockControl() = delete;
    explicit BlockControl(const Board& board);
    ~BlockControl() = default;

    bool move(MoveCommand cmd);
    void dropFull();
    bool canMoveTo(const BlockState& state) const;

    TetrisBlock* getCurrentBlock() { return curControlBlock; }
    void setCurrentBlock(TetrisBlock& block) { curControlBlock = &block; }
};
