#pragma once
#include "Console.h"

struct BlockState {
    int x;
    int y;
    int angle;
};

enum class MoveCommand {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE
};

enum class ItemType {
    NONE = 0,
    A = 2,   // cleared line also removes one line above and below
    B = 3,   // score for this clear is doubled
    C = 4    // next 5 blocks become stick blocks
};

class TetrisBlock
{
private:
    static const char block[7][4][4][4];

    int shape;
    int angle;
    int x;
    int y;
    int stick_rate;
    int color;
    ItemType itemType;

    void move_left(BlockState& state) const;
    void move_right(BlockState& state) const;
    void move_down(BlockState& state) const;
    void move_rotate(BlockState& state) const;

public:
    TetrisBlock(int stick_rate = 20, int forceShape = -1, ItemType forceItem = ItemType::NONE);

    BlockState propose(MoveCommand cmd) const;

    void commit(const BlockState& state);

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
