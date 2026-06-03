#pragma once
#include "Console.h"

// 블록의 가로세로 크기 (ex. 4x4)
constexpr int BLOCK_SIZE = 4;
// 테트리스 기본 블록 종류 수
constexpr int BLOCK_SHAPE_COUNT = 7;
// 블록의 회전 각도 상태 수
constexpr int BLOCK_ANGLE_COUNT = 4;

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
    // 매직넘버 배열 크기를 상수로 교체
    static const unsigned short block[BLOCK_SHAPE_COUNT][BLOCK_ANGLE_COUNT];

    int shape;      // 0~(BLOCK_SHAPE_COUNT-1): 테트리스 기본 블록 모양
    int angle;      // 0~(BLOCK_ANGLE_COUNT-1): 회전 상태
    int x;          // 현재 블록의 왼쪽 위 기준 x 좌표
    int y;          // 현재 블록의 왼쪽 위 기준 y 좌표
    int color;      // Console 출력 색상
    ItemType itemType;

    // 블록을 왼쪽으로 한 칸 이동 상태 기록
    void moveLeft(BlockState& state) const;
    // 블록을 오른쪽으로 한 칸 이동 상태 기록
    void moveRight(BlockState& state) const;
    // 블록을 아래로 한 칸 이동 상태 기록
    void moveDown(BlockState& state) const;
    // 블록을 오른쪽으로 90도 회전 상태 기록
    void rotate(BlockState& state) const;

    // 확률에 기반한 랜덤 블록 모양 선택
    static int selectRandomShape(int stickRate);
    // 확률에 기반한 랜덤 아이템 종류 선택
    static ItemType selectRandomItemType();
    // 모양에 따른 고정 출력 색상 반환
    static int selectColorByShape(int shape);

public:
    // 확률/강제 옵션 적용 블록 생성자
    TetrisBlock(int stickRate = 20, int forceShape = -1, ItemType forceItem = ItemType::NONE);

    // 현재 블록을 직접 바꾸지 않고, 이동 후 후보 상태만 반환한다.
    BlockState propose(MoveCommand cmd) const;

    // 충돌 검사를 통과한 상태를 실제 내부 변수에 반영한다.
    void commit(const BlockState& state);

    // 해당 블록이 아이템을 내장하고 있는지 여부 반환
    bool isItemBlock() const { return itemType != ItemType::NONE; }

    // 비트 연산을 통해 현재 형태, 각도에 대응하는 블록의 특정(i,j) 칸 점유 여부 반환
    static bool getBlockData(int shape, int angle, int i, int j) {
        unsigned short currentBlock = block[shape][angle];
        // 상수 BLOCK_SIZE 기반 비트 인덱스 계산식으로 재설정
        int bitIndex = (BLOCK_SIZE * BLOCK_SIZE - 1) - (i * BLOCK_SIZE + j);
        return (currentBlock >> bitIndex) & 1;
    }

    // X 좌표 반환
    int getX() const { return x; }
    // Y 좌표 반환
    int getY() const { return y; }
    // 현재 회전 각도 반환
    int getAngle() const { return angle; }
    // 블록 모양 인덱스 반환
    int getShape() const { return shape; }
    // 블록 색상 코드 반환
    int getColor() const { return color; }
    // 내장 아이템 타입 반환
    ItemType getItemType() const { return itemType; }
};