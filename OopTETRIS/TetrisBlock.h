#pragma once
#include "Console.h"

// 블록이 이동/회전한 뒤의 후보 상태를 담는 구조체.
struct BlockState {
    int x;
    int y;
    int angle;
};

// 키 입력을 블록 이동 명령으로 추상화한 enum.
// GameManager는 키보드 입력만 해석하고, 실제 이동 계산은 TetrisBlock이 담당한다.
enum class MoveCommand {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE
};

// 아이템 종류.
// 숫자 값은 Board에 저장되는 cell 값과 연결되므로 기존 기능과 호환되게 유지한다.
enum class ItemType {
    NONE = 0,
    A = 2,   // 제거된 줄의 위/아래 줄까지 함께 제거
    B = 3,   // 이번 라인 클리어 점수 2배
    C = 4    // 다음 5개 블록을 I 블록으로 강제 생성
};

class TetrisBlock
{
private:
    static const char block[7][4][4][4];

    int shape;      // 0~6: 테트리스 기본 7개 블록 모양
    int angle;      // 0~3: 회전 상태
    int x;          // 현재 블록의 왼쪽 위 기준 x 좌표
    int y;          // 현재 블록의 왼쪽 위 기준 y 좌표
    int color;      // Console 출력 색상
    ItemType itemType;

    void moveLeft(BlockState& state) const;
    void moveRight(BlockState& state) const;
    void moveDown(BlockState& state) const;
    void rotate(BlockState& state) const;

    static int selectRandomShape(int stickRate);
    static ItemType selectRandomItemType();
    static int selectColorByShape(int shape);

public:
    TetrisBlock(int stickRate = 20, int forceShape = -1, ItemType forceItem = ItemType::NONE);

    // 현재 블록을 직접 바꾸지 않고, 이동 후 후보 상태만 반환한다.
    // 충돌 검사는 Board/BlockControl이 담당한다.
    BlockState propose(MoveCommand cmd) const;

    // 충돌 검사를 통과한 상태만 실제 블록에 반영한다.
    void commit(const BlockState& state);

    bool isItemBlock() const { return itemType != ItemType::NONE; }

    static char getBlockData(int s, int a, int y, int x) {
        return block[s][a][y][x];
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getAngle() const { return angle; }
    int getShape() const { return shape; }
    int getColor() const { return color; }
    ItemType getItemType() const { return itemType; }
};
