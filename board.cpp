#include "board.h"
#include <cstdlib>

void Board::init()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (j == 0 || j == 13)
                cells[i][j] = 1;
            else
                cells[i][j] = 0;
        }
    }

    for (int j = 0; j < 14; j++)
    {
        cells[20][j] = 1;
    }
}

bool Board::isCollision(const BlockState& state,int shape) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(shape,state.angle,i,j) == 1)
            {
                int boardX = state.x + j;
                int boardY = state.y + i;

                if (boardX < 0 ||
                    boardX >= this->getBoardWidth())
                {
                    return true;
                }

                if (boardY >= this->getBoardHeight())
                {
                    return true;
                }

                if (boardY >= 0)
                {
                    if (this->getBoardValue(
                        boardY,
                        boardX) == 1)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void Board::merge(const TetrisBlock& block)
{
    int x = block.getX();
    int y = block.getY();
    int shape = block.getShape();
    int angle = block.getAngle();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(shape, angle, i, j))
            {
                cells[y + i][x + j] = 1;
            }
        }
    }
}

int Board::clearFullLines(int& score, int& lines, int level)
{
    int cleared = 0;

    for (int i = 0; i < 20; i++)
    {
        bool full = true;

        for (int j = 1; j < 13; j++)
        {
            if (cells[i][j] == 0)
            {
                full = false;
                break;
            }
        }

        if (full)
        {
            cleared++;
            lines++;

            for (int k = i; k > 0; k--)
            {
                for (int j = 1; j < 13; j++)
                {
                    cells[k][j] = cells[k - 1][j];
                }
            }

            for (int j = 1; j < 13; j++)
            {
                cells[0][j] = 0;
            }

            score += 100 + (level * 10);
        }
    }

    return cleared;
}

char Board::getCell(int y, int x) const
{
    return cells[y][x];
}