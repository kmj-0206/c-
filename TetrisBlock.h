<<<<<<< HEAD
#pragma once
=======
﻿#pragma once
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
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

<<<<<<< HEAD
enum class ItemType {
    NONE = 0,
    A = 2,   // cleared line also removes one line above and below
    B = 3,   // score for this clear is doubled
    C = 4    // next 5 blocks become stick blocks
};

=======
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
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
<<<<<<< HEAD
    ItemType itemType;
=======
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

    void move_left(BlockState& state) const;
    void move_right(BlockState& state) const;
    void move_down(BlockState& state) const;
    void move_rotate(BlockState& state) const;

public:
<<<<<<< HEAD
    TetrisBlock(int stick_rate = 20, int forceShape = -1, ItemType forceItem = ItemType::NONE);
=======
    TetrisBlock(int stick_rate = 20);
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

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
<<<<<<< HEAD
    ItemType getItemType() const { return itemType; }
};
=======
};
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
