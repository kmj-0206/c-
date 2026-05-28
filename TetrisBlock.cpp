<<<<<<< HEAD
#include "TetrisBlock.h"
=======
﻿#include "TetrisBlock.h"
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
#include <cstdlib>

const char TetrisBlock::block[7][4][4][4] =
{
    {
<<<<<<< HEAD
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}
    },
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
    },
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}
    },
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}
    }
};

TetrisBlock::TetrisBlock(int stick_rate, int forceShape, ItemType forceItem)
    : x(5), y(-4), angle(0), stick_rate(stick_rate), itemType(forceItem)
{
    if (forceShape >= 0 && forceShape <= 6) {
        shape = forceShape;
    }
    else {
        int i = rand() % 100;
        if (i < stick_rate)
            shape = 0;
        else
            shape = (rand() % 6) + 1;
    }

    if (itemType == ItemType::NONE) {
        int r = rand() % 100;
        if (r < 5) itemType = ItemType::A;
        else if (r < 10) itemType = ItemType::B;
        else if (r < 15) itemType = ItemType::C;
    }

    using namespace Console;
=======
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0}
        },
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        }
    },

    {
        {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        }
    },

    {
        {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },

    {
        {
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },

    {
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        }
    },

    {
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },

    {
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    }
};

TetrisBlock::TetrisBlock(int stick_rate)
    : x(5), y(-4), angle(0), stick_rate(stick_rate)
{
    int i = rand() % 100;

    if (i < stick_rate)
        shape = 0;
    else
        shape = (rand() % 6) + 1;

    using namespace Console;

>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    switch (shape)
    {
    case 0: color = RED; break;
    case 1: color = BLUE; break;
    case 2: color = SKY_BLUE; break;
    case 3: color = WHITE; break;
    case 4: color = YELLOW; break;
    case 5: color = VOILET; break;
    case 6: color = GREEN; break;
<<<<<<< HEAD
    default: color = WHITE; break;
=======
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    }
}

BlockState TetrisBlock::propose(MoveCommand cmd) const
{
    BlockState next = { x, y, angle };
<<<<<<< HEAD
    switch (cmd)
    {
    case MoveCommand::LEFT: move_left(next); break;
    case MoveCommand::RIGHT: move_right(next); break;
    case MoveCommand::DOWN: move_down(next); break;
    case MoveCommand::ROTATE: move_rotate(next); break;
    }
=======

    switch (cmd)
    {
    case MoveCommand::LEFT:
        move_left(next);
        break;

    case MoveCommand::RIGHT:
        move_right(next);
        break;

    case MoveCommand::DOWN:
        move_down(next);
        break;

    case MoveCommand::ROTATE:
        move_rotate(next);
        break;
    }

>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    return next;
}

void TetrisBlock::commit(const BlockState& state)
{
    x = state.x;
    y = state.y;
    angle = state.angle;
}

<<<<<<< HEAD
void TetrisBlock::move_left(BlockState& state) const { state.x--; }
void TetrisBlock::move_right(BlockState& state) const { state.x++; }
void TetrisBlock::move_down(BlockState& state) const { state.y++; }
void TetrisBlock::move_rotate(BlockState& state) const { state.angle = (angle + 1) % 4; }
=======
void TetrisBlock::move_left(BlockState& state) const
{
    state.x--;
}

void TetrisBlock::move_right(BlockState& state) const
{
    state.x++;
}

void TetrisBlock::move_down(BlockState& state) const
{
    state.y++;
}

void TetrisBlock::move_rotate(BlockState& state) const
{
    state.angle = (angle + 1) % 4;
}
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
