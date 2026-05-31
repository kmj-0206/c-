#include "Console.h"
#include "TetrisBlock.h"
#include "board.h"
#include <iostream>
#include <string>
#include <conio.h>
void Console::gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void Console::SetColor(int color)
{
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}

void Console::clear()
{
    system("cls");
}

void Console::hideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &info);
}

// mode 0 = 일반 그리기, 1 = 지우기, 2 = 고스트(테두리) 그리기
void Console::drawBlockShape(int shape, int angle, int startX, int startY, int color, int mode)
{
    if (mode == 0) SetColor(color);
    else if (mode == 2) SetColor(DARK_GRAY);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (TetrisBlock::getBlockData(shape, angle, i, j) == 1) {
                if (startY + i < 0) continue;
                gotoxy(startX + j * 2, startY + i);

                if (mode == 1) std::cout << "  ";
                else if (mode == 2) std::cout << "□";
                else std::cout << "■";
            }
        }
    }
    if (mode != 1) SetColor(WHITE);
}



void Console::show_block(const TetrisBlock& block)
{
    drawBlockShape(block.getShape(), block.getAngle(), block.getX() * 2 + ab_x, block.getY() + ab_y, block.getColor(), 0);
}


void Console::erase_block(const TetrisBlock& block)
{
    drawBlockShape(block.getShape(), block.getAngle(), block.getX() * 2 + ab_x, block.getY() + ab_y, BLACK, 1);
}

void Console::drawGhostBlock(const TetrisBlock& block, const Board& board)
{
    TetrisBlock ghost = block;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape())) {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }
    drawBlockShape(ghost.getShape(), ghost.getAngle(), ghost.getX() * 2 + ab_x, ghost.getY() + ab_y, 0, 2);
}

void Console::drawTitle()
{
    clear();
    hideCursor();

    SetColor(SKY_BLUE);
    std::cout << "\n\n\n\n";
    std::cout << "\t\t  TTTTT EEEEE TTTTT RRRR  IIIII SSSSS\n";
    std::cout << "\t\t    T   E       T   R   R   I   S    \n";
    std::cout << "\t\t    T   EEE     T   RRRR    I   SSSSS\n";
    std::cout << "\t\t    T   E       T   R R     I       S\n";
    std::cout << "\t\t    T   EEEEE   T   R  RR IIIII SSSSS\n\n\n";

    SetColor(WHITE);
    gotoxy(24, 12);
    std::cout << "Press any key to start...  \n";

    int shapeCounter = 0;
    ULONGLONG lastUpdate = GetTickCount64();

    TetrisBlock demoBlock(20, shapeCounter, ItemType::NONE);
    demoBlock.commit({ 6, 15, 0 });
    show_block(demoBlock);

    while (!_kbhit())
    {
        ULONGLONG now = GetTickCount64();
        if (now - lastUpdate >= 1000)
        {
            erase_block(demoBlock);

            shapeCounter = (shapeCounter + 1) % 7;
            int nextAngle = (demoBlock.getAngle() + 1) % 4;

            demoBlock = TetrisBlock(20, shapeCounter, ItemType::NONE);
            demoBlock.commit({ 6, 15, nextAngle });

            show_block(demoBlock);
            lastUpdate = now;
        }
        Sleep(30);
    }
    _getch();
}

void Console::drawBoard(const Board& board)
{
    for (int y = 0; y < board.getBoardHeight(); y++)
    {
        for (int x = 0; x < board.getBoardWidth(); x++)
        {
            gotoxy(x * 2 + ab_x, y + ab_y);
            if (board.getBoardValue(y, x))
                std::cout << "■";
            else
                std::cout << "  ";
        }
    }
}

void Console::drawInfo(int score, int remainingLines, int level, int comboMultiplier, int difficulty)
{
    gotoxy(40, 3); std::cout << "Score : " << score << "      ";
    gotoxy(40, 5); std::cout << "Lines Left: " << remainingLines << "      "; //남은 라인
    gotoxy(40, 7); std::cout << "Level : " << level + 1 << "      ";
    gotoxy(40, 9); std::cout << "Combo : x" << comboMultiplier << "      ";
    gotoxy(40, 11); std::cout << "Difficulty : " << difficulty << "      ";
}
void Console::drawNextBlocks(const std::vector<TetrisBlock>& nextBlocks)
{
    const int baseX = 62;
    const int baseY = 2;
    SetColor(WHITE);
    gotoxy(baseX, baseY - 1); std::cout << "NEXT 5";

    for (int n = 0; n < 5; n++)
    {
        int yOffset = baseY + n * 4;
        for (int r = 0; r < 4; r++) {
            gotoxy(baseX, yOffset + r);
            std::cout << "        ";
        }

        if (n >= static_cast<int>(nextBlocks.size())) continue;
        const TetrisBlock& block = nextBlocks[n];

        // 4중 for문 삭제 후 단일 함수로 대체
        drawBlockShape(block.getShape(), 0, baseX, yOffset, block.getColor(), 0);
    }
}

void Console::drawRankings(const std::vector<int>& ranks)
{
    const int x = 40;
    const int y = 14;
    SetColor(WHITE);
    gotoxy(x, y); std::cout << "RANK TOP 3";
    for (int i = 0; i < 3; i++)
    {
        gotoxy(x, y + 2 + i);
        if (i < static_cast<int>(ranks.size()))
            std::cout << i + 1 << ". " << ranks[i] << "        ";
        else
            std::cout << i + 1 << ". -        ";
    }
}

void Console::drawGameOver()
{
    gotoxy(40, 20);
    SetColor(RED);
    std::cout << "GAME OVER";
    SetColor(WHITE);
}
void Console::drawGameClear()
{
    gotoxy(40, 20);
    SetColor(SKY_BLUE);
    std::cout << "GAME CLEAR!!";
    SetColor(WHITE);
}


void Console::initRenderBuffer(char buffer[21][14], const Board& board)
{
    for (int y = 0; y < 21; y++) { // 20 -> 21로 변경 (바닥 포함)
        for (int x = 0; x < 14; x++) {
            buffer[y][x] = board.getBoardValue(y, x);
        }
    }
}

void Console::applyBlocksToBuffer(char buffer[21][14], const Board& board, const TetrisBlock& current)
{
    TetrisBlock ghost = current;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape())) {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (TetrisBlock::getBlockData(ghost.getShape(), ghost.getAngle(), i, j) == 1) {
                int by = ghost.getY() + i;
                int bx = ghost.getX() + j;
                // y의 한계치도 21로 변경
                if (by >= 0 && by < 21 && bx >= 0 && bx < 14 && buffer[by][bx] == 0) {
                    buffer[by][bx] = 5;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (TetrisBlock::getBlockData(current.getShape(), current.getAngle(), i, j) == 1) {
                int by = current.getY() + i;
                int bx = current.getX() + j;
                if (by >= 0 && by < 21 && bx >= 0 && bx < 14) {
                    buffer[by][bx] = 6;
                }
            }
        }
    }
}

// shadowBuffer를 전역으로 빼서 clear가 가능하게 
static char shadowBuffer[21][14] = { 0 };

void Console::clearShadowBuffer()
{
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 14; x++) {
            shadowBuffer[y][x] = 0;
        }
    }
}

void Console::renderGameBuffer(const char buffer[21][14], int currentBlockColor)
{
    for (int y = 0; y < 21; y++) { // 20 -> 21로 변경
        for (int x = 0; x < 14; x++) {
            if (buffer[y][x] != shadowBuffer[y][x]) {
                gotoxy(x * 2 + ab_x, y + ab_y);
                switch (buffer[y][x]) {
                case 0:  std::cout << "  "; break;
                case 5:  SetColor(DARK_GRAY); std::cout << "□"; break;
                case 6:  SetColor(currentBlockColor); std::cout << "■"; break;
                default: SetColor(WHITE); std::cout << "■"; break;
                }
                shadowBuffer[y][x] = buffer[y][x];
            }
        }
    }
    SetColor(WHITE);
}

void Console::drawGameField(const Board& board, const TetrisBlock& current)
{
    // 1. 그릴 내용을 담을 21x14 도화지(버퍼) 생성
    char buffer[21][14] = { 0 };

    // 2. 보드(배경 및 고정된 블록) 복사
    for (int y = 0; y < board.getBoardHeight(); y++) {
        for (int x = 0; x < board.getBoardWidth(); x++) {
            buffer[y][x] = board.getBoardValue(y, x);
        }
    }

    // 3. 고스트 블록 찍기 (값 5)
    TetrisBlock ghost = current;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape())) {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (TetrisBlock::getBlockData(ghost.getShape(), ghost.getAngle(), i, j) == 1) {
                int by = ghost.getY() + i;
                int bx = ghost.getX() + j;
                if (by >= 0 && by < 21 && bx >= 0 && bx < 14) {
                    if (buffer[by][bx] == 0) buffer[by][bx] = 5;
                }
            }
        }
    }

    // 4. 현재 조작 중인 블록 찍기 (값 6) - 이렇게 하면 고스트 블록 위에 안전하게 덮어씌워집니다.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (TetrisBlock::getBlockData(current.getShape(), current.getAngle(), i, j) == 1) {
                int by = current.getY() + i;
                int bx = current.getX() + j;
                if (by >= 0 && by < 21 && bx >= 0 && bx < 14) {
                    buffer[by][bx] = 6;
                }
            }
        }
    }

    // 바뀐 곳만  콘솔에 출력 (깜빡임 제거)
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 14; x++) {
            if (buffer[y][x] != shadowBuffer[y][x]) {
                gotoxy(x * 2 + ab_x, y + ab_y);

                switch (buffer[y][x]) {
                case 0:  std::cout << "  "; break; // 빈칸
                case 5:  SetColor(DARK_GRAY); std::cout << "□"; break; // 고스트
                case 6:  SetColor(current.getColor()); std::cout << "■"; break; // 현재블록
                default: SetColor(WHITE); std::cout << "■"; break; // 바닥, 벽, 굳은 블록
                }
                shadowBuffer[y][x] = buffer[y][x];
            }
        }
    }
    SetColor(WHITE);
}