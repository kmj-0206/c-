#include "board.h"

void board::init()
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

bool board::isCollision(const TetrisBlock& block)
{
    int x = block.getX();
    int y = block.getY();
    int shape = block.getShape();
    int angle = block.getAngle();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int boardData = 0;

            if ((x + j) == 0 || (x + j) == 13)
            {
                boardData = 1;
            }
            else if (y + i >= 0 && x + j >= 0)
            {
                boardData = cells[y + i][x + j];
            }

            if (boardData == 1 &&
                TetrisBlock::getBlockData(shape, angle, i, j) == 1)
            {
                return true;
            }
        }
    }

    return false;
}

void board::merge(const TetrisBlock& block)
{
    int x = block.getX();
    int y = block.getY();
    int shape = block.getShape();
    int angle = block.getAngle();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cells[y + i][x + j] |=
                TetrisBlock::getBlockData(shape, angle, i, j);
        }
    }
}
}

int board::clearFullLines(int& score, int& lines, int level)
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

            score += 100 + (level * 10) + (rand() % 10);
        }
    }

    return cleared;
}

char board::getCell(int y, int x) const
{
    return cells[y][x];
}
