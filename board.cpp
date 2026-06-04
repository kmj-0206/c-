#include "board.h"

bool Board::isInsidePlayableX(int x) const
{
    return x > BOARD_LEFT_WALL && x < BOARD_RIGHT_WALL;
}

bool Board::isInsidePlayableY(int y) const
{
    return y >= 0 && y < BOARD_PLAY_HEIGHT;
}

ItemType Board::cellToItemType(char value) const
{
    if (value == static_cast<char>(ItemType::A)) return ItemType::A;
    if (value == static_cast<char>(ItemType::B)) return ItemType::B;
    if (value == static_cast<char>(ItemType::C)) return ItemType::C;
    return ItemType::NONE;
}

void Board::init()
{
    // 실제 플레이 영역 초기화.
    // 양쪽 벽은 1, 빈칸은 0으로 저장한다.
    for (int y = 0; y < BOARD_PLAY_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x == BOARD_LEFT_WALL || x == BOARD_RIGHT_WALL)
                cells[y][x] = 1;
            else
                cells[y][x] = 0;
        }
    }

    // 맨 아래 한 줄은 바닥 벽으로 사용한다.
    for (int x = 0; x < BOARD_WIDTH; x++)
        cells[BOARD_PLAY_HEIGHT][x] = 1;
}

bool Board::isCollision(const BlockState& state, int shape) const
{
    for (int y = 0; y < BLOCK_SIZE; y++)
    {
        for (int x = 0; x < BLOCK_SIZE; x++)
        {
            if (TetrisBlock::getBlockData(shape, state.angle, y, x) == 0)
                continue;

            int boardX = state.x + x;
            int boardY = state.y + y;

            // 화면 위쪽(boardY < 0)은 아직 보이지 않는 생성 영역이므로 허용한다.
            // 단, 좌우 벽과 바닥은 항상 충돌로 처리한다.
            if (!isInsidePlayableX(boardX))
                return true;

            if (boardY >= BOARD_HEIGHT)
                return true;

            if (boardY >= 0 && cells[boardY][boardX] != 0)
                return true;
        }
    }

    return false;
}

void Board::merge(const TetrisBlock& block)
{
    int startX = block.getX();
    int startY = block.getY();
    int shape = block.getShape();
    int angle = block.getAngle();

    // 일반 고정 블록은 7, 아이템 블록은 ItemType 값(2,3,4)을 그대로 저장한다.
    // Console.cpp가 이 숫자를 보고 A/B/C를 출력한다.
    char cellValue = 7;
    if (block.isItemBlock())
        cellValue = static_cast<char>(block.getItemType());

    for (int y = 0; y < BLOCK_SIZE; y++)
    {
        for (int x = 0; x < BLOCK_SIZE; x++)
        {
            if (TetrisBlock::getBlockData(shape, angle, y, x) == 0)
                continue;

            int boardY = startY + y;
            int boardX = startX + x;

            // 화면 위쪽에 걸친 블록은 실제 보드에 기록하지 않는다.
            if (isInsidePlayableY(boardY) && isInsidePlayableX(boardX))
                cells[boardY][boardX] = cellValue;
        }
    }
}

ClearResult Board::checkClearLines() const
{
    ClearResult result;

    for (int y = 0; y < BOARD_PLAY_HEIGHT; y++)
    {
        bool full = true;

        for (int x = 1; x < BOARD_RIGHT_WALL; x++)
        {
            if (cells[y][x] == 0)
            {
                full = false;
                break;
            }
        }

        if (!full)
            continue;

        result.fullLines++;
        result.removedRows.insert(y);

        // 꽉 찬 줄 안에 들어 있는 아이템 종류를 기록한다.
        // 실제 효과 적용은 ItemEffectManager에게 위임한다.
        for (int x = 1; x < BOARD_RIGHT_WALL; x++)
            result.markItem(cellToItemType(cells[y][x]));
    }

    return result;
}
// namespace 혼용 방지를 위해 std 냅두기
void Board::removeLines(const std::set<int>& rowsToRemove)
{
    if (rowsToRemove.empty())
        return;

    char newCells[BOARD_HEIGHT][BOARD_WIDTH] = {};

    // 새 보드의 벽/빈칸/바닥을 먼저 만든다.
    for (int y = 0; y < BOARD_PLAY_HEIGHT; y++)
    {
        newCells[y][BOARD_LEFT_WALL] = 1;
        newCells[y][BOARD_RIGHT_WALL] = 1;
        for (int x = 1; x < BOARD_RIGHT_WALL; x++)
            newCells[y][x] = 0;
    }

    for (int x = 0; x < BOARD_WIDTH; x++)
        newCells[BOARD_PLAY_HEIGHT][x] = 1;

    // 아래쪽부터 읽으면서 제거 대상이 아닌 줄만 아래로 압축한다.
    int writeY = BOARD_PLAY_HEIGHT - 1;
    for (int readY = BOARD_PLAY_HEIGHT - 1; readY >= 0; readY--)
    {
        if (rowsToRemove.count(readY) != 0)
            continue;

        for (int x = 1; x < BOARD_RIGHT_WALL; x++)
            newCells[writeY][x] = cells[readY][x];

        writeY--;
    }

    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++)
            cells[y][x] = newCells[y][x];
}


