#pragma once
#include "TetrisBlock.h"

class Board;

class BlockControl
{
private:
    TetrisBlock* curControlBlock; // 현재 조작 중인 블록. 소유하지 않고 참조만 한다.
    const Board* curBoard;        // 충돌 검사용 보드. 소유하지 않는다.

public:
    // 기본 생성자 삭제
    BlockControl() = delete;
    // 보드를 참조하는 생성자
    explicit BlockControl(const Board& board);
    // 기본 소멸자
    ~BlockControl() = default;

    // 블록 이동 시도
    bool move(MoveCommand cmd);
    // 블록 하드 드롭 (바닥까지 즉시 내림)
    void dropFull();
    // 해당 상태(위치/회전)로 이동 가능한지 확인
    bool canMoveTo(const BlockState& state) const;

    // 현재 조작 중인 블록 객체 반환
    TetrisBlock* getCurrentBlock() { return curControlBlock; }
    // 조작할 대상 블록 설정
    void setCurrentBlock(TetrisBlock& block) { curControlBlock = &block; }
};