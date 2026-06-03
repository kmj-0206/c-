#pragma once
#include "TetrisBlock.h"
#include <set>

// 보드 크기와 cell 값은 Board 한 곳에서 관리한다.
// 일단은, 출력의 안정성을 위해 게임중에 함부로 값은 변경하지 않는다.
constexpr int BOARD_HEIGHT = 21;      // 0~19: 실제 필드, 20: 바닥 벽
constexpr int BOARD_PLAY_HEIGHT = 20;
constexpr int BOARD_WIDTH = 14;       // 0, 13: 좌우 벽
constexpr int BOARD_LEFT_WALL = 0;
constexpr int BOARD_RIGHT_WALL = 13;

struct ClearResult {
    int fullLines = 0;                 // 실제로 꽉 찬 줄 수. 점수 계산은 이 값으로 한다.
    std::set<int> removedRows;         // 애니메이션/삭제 대상 줄. 아이템 A로 확장될 수 있다.std 혼자 사용 
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

    // X 좌표가 보드 내부인지 확인
    bool isInsidePlayableX(int x) const;
    // Y 좌표가 보드 내부인지 확인
    bool isInsidePlayableY(int y) const;
    // 보드 셀 값을 ItemType으로 변환
    ItemType cellToItemType(char value) const;

public:
    // 보드 배열 초기화
    void init();

    // 블록과 보드의 충돌 여부 확인
    bool isCollision(const BlockState& state, int shape) const;
    // 굳은 블록을 보드 배열에 병합
    void merge(const TetrisBlock& block);

    // 꽉 찬 줄 탐색 및 라인 정보 반환
    ClearResult checkClearLines() const;
    // 지정된 줄 제거 및 위쪽 블록 내리기
    void removeLines(const std::set<int>& rowsToRemove);

    

    //// 보드 너비 반환
    //int getBoardWidth() const { return BOARD_WIDTH; }
    //// 보드 높이 반환
    //int getBoardHeight() const { return BOARD_HEIGHT; }

    // 특정 좌표의 보드 값 반환
    char getBoardValue(int y, int x) const { return cells[y][x]; }
};
