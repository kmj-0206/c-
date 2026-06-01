#pragma once
#include "TetrisBlock.h"
#include <set>

// 보드 크기와 cell 값은 Board 한 곳에서 관리한다.
// Console.cpp는 기존 숫자 값을 기준으로 출력하므로 값은 변경하지 않는다.
constexpr int BOARD_HEIGHT = 21;      // 0~19: 실제 필드, 20: 바닥 벽
constexpr int BOARD_PLAY_HEIGHT = 20;
constexpr int BOARD_WIDTH = 14;       // 0, 13: 좌우 벽
constexpr int BOARD_LEFT_WALL = 0;
constexpr int BOARD_RIGHT_WALL = 13;

struct ClearResult {
    int fullLines = 0;                 // 실제로 꽉 찬 줄 수. 점수 계산은 이 값으로 한다.
    std::set<int> removedRows;         // 애니메이션/삭제 대상 줄. 아이템 A로 확장될 수 있다.
    bool itemA = false;
    bool itemB = false;
    bool itemC = false;

    bool hasClearedLine() const { return fullLines > 0; }

    bool hasItem(ItemType type) const
    {
        switch (type)
        {
        case ItemType::A: return itemA;
        case ItemType::B: return itemB;
        case ItemType::C: return itemC;
        default: return false;
        }
    }

    void markItem(ItemType type)
    {
        switch (type)
        {
        case ItemType::A: itemA = true; break;
        case ItemType::B: itemB = true; break;
        case ItemType::C: itemC = true; break;
        default: break;
        }
    }
};

class Board
{
private:
    char cells[BOARD_HEIGHT][BOARD_WIDTH];

    bool isInsidePlayableX(int x) const;
    bool isInsidePlayableY(int y) const;
    ItemType cellToItemType(char value) const;

public:
    void init();

    bool isCollision(const BlockState& state, int shape) const;
    void merge(const TetrisBlock& block);

    // 꽉 찬 줄과 해당 줄에 포함된 아이템 종류만 탐지한다.
    // 아이템 효과 적용은 ItemEffectManager가 담당한다.
    ClearResult checkClearLines() const;
    void removeLines(const std::set<int>& rowsToRemove);

    char getCell(int y, int x) const;

    int getBoardWidth() const { return BOARD_WIDTH; }
    int getBoardHeight() const { return BOARD_HEIGHT; }

    char getBoardValue(int y, int x) const { return cells[y][x]; }
};
