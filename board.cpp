#include "board.h"
#include <set>
#include <vector>

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

bool Board::isCollision(const BlockState& state, int shape) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(shape, state.angle, i, j) == 1)
            {
                int boardX = state.x + j;
                int boardY = state.y + i;

                // y좌표(화면 위/아래)와 상관없이, 
                // 왼쪽 벽(x=0) 이하이거나 오른쪽 벽(x=13) 이상으로 나가려 하면 충돌
                if (boardX <= 0 || boardX >= this->getBoardWidth() - 1)
                    return true;

                // 화면 바닥을 완전히 뚫고 내려가는 것 방지
                if (boardY >= this->getBoardHeight())
                    return true;

                // 2. 화면 내부(y >= 0)에 진입했을 때만 보드판 데이터(바닥 및 고정 블록) 검사
                if (boardY >= 0 && this->getBoardValue(boardY, boardX) != 0)
                    return true;
            }
        }
    }

    return false;
}
void Board::merge(const TetrisBlock& block)
{
    //굳을 블록의 데이터
    int x = block.getX();
    int y = block.getY();
    int shape = block.getShape();
    int angle = block.getAngle();
    char value = 7; 

    if (block.getItemType() == ItemType::A) value = 2;
    else if (block.getItemType() == ItemType::B) value = 3;
    else if (block.getItemType() == ItemType::C) value = 4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(shape, angle, i, j))
            {
                int by = y + i;
                int bx = x + j;
                if (by >= 0 && by < 20 && bx > 0 && bx < 13)
                    cells[by][bx] = value;
            }
        }
    }
}
//다 찾는지 확인만 하는 용도. //애니메이션과 로직을 분리하기 위해서.
ClearResult Board::checkClearLines()
{
    ClearResult result = { 0, {}, false, false, false };

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
            result.fullLines++;
            result.removedRows.insert(i);

            bool rowHasItemA = false;
            for (int j = 1; j < 13; j++)
            {
                if (cells[i][j] == 2) { result.itemA = true; rowHasItemA = true; }
                if (cells[i][j] == 3) result.itemB = true;
                if (cells[i][j] == 4) result.itemC = true;
            }

            if (rowHasItemA)
            {
                if (i - 1 >= 0) result.removedRows.insert(i - 1);
                if (i + 1 < 20) result.removedRows.insert(i + 1);
            }
        }
    }

    return result;
}
void Board::removeLines(const std::set<int>& rowsToRemove)
{
    if (rowsToRemove.empty())
        return;

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
}
char Board::getCell(int y, int x) const
{
    return cells[y][x];
}
