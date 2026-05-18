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

    void move_left(BlockState& state) const;
    void move_right(BlockState& state) const;
    void move_down(BlockState& state) const;
    void move_rotate(BlockState& state) const;

public:
    TetrisBlock(int stick_rate = 20);

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
};