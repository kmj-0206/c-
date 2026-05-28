<<<<<<< HEAD
#include "board.h"
#include <set>
#include <vector>
=======
﻿#include "board.h"
#include <cstdlib>
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

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

<<<<<<< HEAD
bool Board::isCollision(const BlockState& state, int shape) const
=======
bool Board::isCollision(const BlockState& state,int shape) const
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
<<<<<<< HEAD
            if (TetrisBlock::getBlockData(shape, state.angle, i, j) == 1)
=======
            if (TetrisBlock::getBlockData(shape,state.angle,i,j) == 1)
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
            {
                int boardX = state.x + j;
                int boardY = state.y + i;

<<<<<<< HEAD
                if (boardX < 0 || boardX >= this->getBoardWidth())
                    return true;

                if (boardY >= this->getBoardHeight())
                    return true;

                if (boardY >= 0 && this->getBoardValue(boardY, boardX) != 0)
                    return true;
=======
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
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
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
<<<<<<< HEAD
    char value = 1;

    if (block.getItemType() == ItemType::A) value = 2;
    else if (block.getItemType() == ItemType::B) value = 3;
    else if (block.getItemType() == ItemType::C) value = 4;
=======
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(shape, angle, i, j))
            {
<<<<<<< HEAD
                int by = y + i;
                int bx = x + j;
                if (by >= 0 && by < 20 && bx > 0 && bx < 13)
                    cells[by][bx] = value;
=======
                cells[y + i][x + j] = 1;
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
            }
        }
    }
}

<<<<<<< HEAD
ClearResult Board::clearFullLines()
{
    ClearResult result = { 0, 0, false, false, false };
    std::set<int> rowsToRemove;
=======
int Board::clearFullLines(int& score, int& lines, int level)
{
    int cleared = 0;
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f

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
<<<<<<< HEAD
            result.fullLines++;
            rowsToRemove.insert(i);

            bool rowHasItemA = false;
            for (int j = 1; j < 13; j++)
            {
                if (cells[i][j] == 2) { result.itemA = true; rowHasItemA = true; }
                if (cells[i][j] == 3) result.itemB = true;
                if (cells[i][j] == 4) result.itemC = true;
            }

            if (rowHasItemA)
            {
                if (i - 1 >= 0) rowsToRemove.insert(i - 1);
                if (i + 1 < 20) rowsToRemove.insert(i + 1);
            }
        }
    }

    if (rowsToRemove.empty())
        return result;

    result.removedRows = static_cast<int>(rowsToRemove.size());

    char newCells[21][14] = {};
    for (int y = 0; y < 20; y++)
    {
        newCells[y][0] = 1;
        newCells[y][13] = 1;
        for (int x = 1; x < 13; x++)
            newCells[y][x] = 0;
    }
    for (int x = 0; x < 14; x++)
        newCells[20][x] = 1;

    int writeY = 19;
    for (int readY = 19; readY >= 0; readY--)
    {
        if (rowsToRemove.count(readY) != 0)
            continue;

        for (int x = 1; x < 13; x++)
            newCells[writeY][x] = cells[readY][x];
        writeY--;
    }

    for (int y = 0; y < 21; y++)
        for (int x = 0; x < 14; x++)
            cells[y][x] = newCells[y][x];

    return result;
=======
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
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
}

char Board::getCell(int y, int x) const
{
    return cells[y][x];
<<<<<<< HEAD
}
=======
}
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
