#include "TetrisBlock.h"
#include <cstdlib>
// 상수 BLOCK_SHAPE_COUNT 적용
const unsigned short TetrisBlock::block[BLOCK_SHAPE_COUNT][BLOCK_ANGLE_COUNT] = {
    {0x0F00, 0x2222, 0x0F00, 0x4444}, // I 블록
    {0x8E00, 0x6440, 0x0E20, 0x44C0}, // J 블록
    {0x2E00, 0x4460, 0x0E80, 0xC440}, // L 블록
    {0x6600, 0x6600, 0x6600, 0x6600}, // O 블록
    {0x6C00, 0x4620, 0x6C00, 0x4620}, // S 블록
    {0x4E00, 0x4640, 0x0E40, 0x4C40}, // T 블록
    {0xC600, 0x2640, 0xC600, 0x2640}  // Z 블록
};

int TetrisBlock::selectRandomShape(int stickRate)
{
    int randomValue = rand() % 100;
    if (randomValue < stickRate)
        return 0;

    // 상수 BLOCK_SHAPE_COUNT 활용하여 1 ~ (BLOCK_SHAPE_COUNT - 1) 범위 반환
    return (rand() % (BLOCK_SHAPE_COUNT - 1)) + 1;
}

ItemType TetrisBlock::selectRandomItemType()
{
    // 기존 아이템 등장 확률 유지:
    // A 5%, B 5%, C 5%, 일반 블록 85%
    int randomValue = rand() % 100;

    if (randomValue < 5) return ItemType::A;
    if (randomValue < 10) return ItemType::B;
    if (randomValue < 15) return ItemType::C;
    return ItemType::NONE;
}

int TetrisBlock::selectColorByShape(int shape)
{
    using namespace Console;

    switch (shape)
    {
    case 0: return RED;
    case 1: return BLUE;
    case 2: return SKY_BLUE;
    case 3: return WHITE;
    case 4: return YELLOW;
    case 5: return VOILET;
    case 6: return GREEN;
    default: return WHITE;
    }
}

TetrisBlock::TetrisBlock(int stickRate, int forceShape, ItemType forceItem)
    : shape(0), angle(0), x(5), y(-4), color(Console::WHITE), itemType(forceItem)
{
    // forceShape가 정상 범위면 강제 모양을 사용하고,
    // 아니면 현재 스테이지 확률에 따라 랜덤 생성한다.
    if (forceShape >= 0 && forceShape <= 6)
        shape = forceShape;
    else
        shape = selectRandomShape(stickRate);

    // 강제 아이템이 없다면 일반 확률에 따라 아이템을 부여한다.
    if (itemType == ItemType::NONE)
        itemType = selectRandomItemType();

    color = selectColorByShape(shape);
}

BlockState TetrisBlock::propose(MoveCommand cmd) const
{
    BlockState next = { x, y, angle };

    switch (cmd)
    {
    case MoveCommand::LEFT:   moveLeft(next);  break;
    case MoveCommand::RIGHT:  moveRight(next); break;
    case MoveCommand::DOWN:   moveDown(next);  break;
    case MoveCommand::ROTATE: rotate(next);    break;
    }

    return next;
}

void TetrisBlock::commit(const BlockState& state)
{
    x = state.x;
    y = state.y;
    angle = state.angle;
}

void TetrisBlock::moveLeft(BlockState& state) const
{
    state.x--;
}

void TetrisBlock::moveRight(BlockState& state) const
{
    state.x++;
}

void TetrisBlock::moveDown(BlockState& state) const
{
    state.y++;
}

void TetrisBlock::rotate(BlockState& state) const
{
    state.angle = (angle + 1) % 4;
}
