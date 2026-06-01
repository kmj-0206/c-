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

    char miniBoard[12][6] = { 0 };
    int my = -4, mx = 1, mShape = rand() % 7;
    ULONGLONG lastUpdate = GetTickCount64();

    while (!_kbhit())
    {
        ULONGLONG now = GetTickCount64();
        if (now - lastUpdate >= 100)
        {
            my++;
            bool coll = false;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (TetrisBlock::getBlockData(mShape, 0, i, j)) {
                        int by = my + i, bx = mx + j;
                        if (by >= 12 || bx < 0 || bx >= 6 || (by >= 0 && miniBoard[by][bx])) coll = true;
                    }
                }
            }

            if (coll) {
                my--;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (TetrisBlock::getBlockData(mShape, 0, i, j)) {
                            int by = my + i, bx = mx + j;
                            if (by >= 0 && by < 12 && bx >= 0 && bx < 6) miniBoard[by][bx] = 1;
                        }
                    }
                }

                // 블록이 꼭대기에서 굳어버렸다면 미니 보드 전체를 지우고 무한 반복
                if (my <= 0) {
                    for (int r = 0; r < 12; r++) {
                        for (int c = 0; c < 6; c++) {
                            miniBoard[r][c] = 0;
                        }
                    }
                }
                else {
                    for (int r = 11; r >= 0; r--) {
                        bool full = true;
                        for (int c = 0; c < 6; c++) if (!miniBoard[r][c]) full = false;
                        if (full) {
                            for (int y2 = r; y2 > 0; y2--)
                                for (int c = 0; c < 6; c++) miniBoard[y2][c] = miniBoard[y2 - 1][c];
                            r++;
                        }
                    }
                }
                my = -4; mx = rand() % 3; mShape = rand() % 7;
            }

            for (int r = 0; r < 12; r++) {
                gotoxy(30, 14 + r);
                SetColor(WHITE); std::cout << "│";
                for (int c = 0; c < 6; c++) {
                    bool isCur = false;
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (TetrisBlock::getBlockData(mShape, 0, i, j) && my + i == r && mx + j == c) isCur = true;
                        }
                    }
                    if (miniBoard[r][c] || isCur) { SetColor(GRAY); std::cout << "■"; }
                    else std::cout << "  ";
                }
                SetColor(WHITE); std::cout << "│";
            }
            gotoxy(30, 14 + 12); std::cout << "└────────────┘";
            lastUpdate = now;
        }
        Sleep(10);
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
    SetColor(WHITE);
    gotoxy(40, 3); std::cout << "Score : " << score << "      ";
    gotoxy(40, 5); std::cout << "Lines Left: " << remainingLines << "      ";
    gotoxy(40, 7); std::cout << "Level : " << level + 1 << "      ";

    // 콤보 숫자만 눈에 띄게 빨간색으로 강조
    gotoxy(40, 9);
    std::cout << "Combo : ";
    if (comboMultiplier == 1) SetColor(WHITE);
    else SetColor(RED);
    std::cout << "x" << comboMultiplier << "      ";

    SetColor(WHITE);
    gotoxy(40, 11); std::cout << "Difficulty : " << difficulty << "      ";

    // 아이템 정보 UI
    gotoxy(40, 14); SetColor(SKY_BLUE); std::cout << "[ Item Info ]";
    gotoxy(40, 15); SetColor(RED); std::cout << "A"; SetColor(WHITE); std::cout << " : Boom!!";
    gotoxy(40, 16); SetColor(BLUE); std::cout << "B"; SetColor(WHITE); std::cout << " : Double score";
    gotoxy(40, 17); SetColor(YELLOW); std::cout << "C"; SetColor(WHITE); std::cout << " : 5 sticks";
    SetColor(WHITE);
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

        // 1. NEXT 블록에도 아이템 알파벳 표시
        int itemVal = 0;
        if (block.getItemType() == ItemType::A) itemVal = 1;
        else if (block.getItemType() == ItemType::B) itemVal = 2;
        else if (block.getItemType() == ItemType::C) itemVal = 3;

        if (itemVal == 1) SetColor(RED);
        else if (itemVal == 2) SetColor(BLUE);
        else if (itemVal == 3) SetColor(YELLOW);
        else SetColor(block.getColor());

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (TetrisBlock::getBlockData(block.getShape(), 0, i, j) == 1) {
                    gotoxy(baseX + j * 2, yOffset + i);
                    if (itemVal == 1) std::cout << "A ";
                    else if (itemVal == 2) std::cout << "B ";
                    else if (itemVal == 3) std::cout << "C ";
                    else std::cout << "■";
                }
            }
        }
        SetColor(WHITE);
    }
}
void Console::drawSideRankings(const std::vector<int>& ranks)
{
    const int x = 40;
    const int y = 20;
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
// 화려한 전체 랭킹 화면 UI 추가
void Console::drawFullRankings(const std::vector<int>& ranks)
{
    clear();
    SetColor(SKY_BLUE);

    // 제목 위치를 위로 올립니다 (\n 텍스트 대신 gotoxy 사용)
    gotoxy(28, 2);
    std::cout << "========== R A N K I N G S ==========";

    for (int i = 0; i < 10; i++) {
        if (i == 0) SetColor(YELLOW);         // 1위 금색
        else if (i == 1) SetColor(GRAY);      // 2위 은색
        else if (i == 2) SetColor(DARK_YELLOW); // 3위 동색
        else SetColor(WHITE);                 // 나머지

        // 스코어 리스트의 Y좌표 시작점을 기존보다 위쪽(4)으로 당깁니다
        gotoxy(32, 5 + i * 2);

        // 1~9위와 10위의 글자 길이 차이를 맞춰 정렬합니다
        std::string rankSpacing = (i < 9) ? "  " : " ";

        if (i < static_cast<int>(ranks.size()))
            std::cout << "Rank" << rankSpacing << i + 1 << "\t\t" << ranks[i] << " Pts";
        else
            std::cout << "Rank" << rankSpacing << i + 1 << "\t\t- Pts";
    }
    SetColor(WHITE);
}
void Console::drawGameOver()
{
    gotoxy(20, 10);
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

void Console::drawGameField(const Board& board, const TetrisBlock& current,int level, const std::set<int>& flashRows, bool isFlash)
{
    char buffer[21][14] = { 0 };

    // ★ 스테이지(레벨)에 따른 "벽(테두리)" 색상 결정 (흰색 -> 주황색 -> 빨간색 순서)
    int borderColor = WHITE;
    if (level == 1) borderColor = YELLOW;             // 2스테이지 (레벨1): 밝은 주황
    else if (level == 2) borderColor = DARK_YELLOW;   // 3스테이지 (레벨2): 짙은 주황
    else if (level == 3) borderColor = RED;           // 4스테이지 (레벨3): 빨간색
    else if (level >= 4) borderColor = DARK_RED;      // 5스테이지 (레벨4): 진한 빨간색

    for (int y = 0; y < board.getBoardHeight(); y++) {
        for (int x = 0; x < board.getBoardWidth(); x++) {
            buffer[y][x] = board.getBoardValue(y, x);
        }
    }

    if (!isFlash) {
        TetrisBlock ghost = current;
        BlockState next = ghost.propose(MoveCommand::DOWN);
        while (!board.isCollision(next, ghost.getShape())) {
            ghost.commit(next);
            next = ghost.propose(MoveCommand::DOWN);
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (TetrisBlock::getBlockData(ghost.getShape(), ghost.getAngle(), i, j) == 1) {
                    int by = ghost.getY() + i, bx = ghost.getX() + j;
                    if (by >= 0 && by < 21 && bx >= 0 && bx < 14 && buffer[by][bx] == 0) buffer[by][bx] = 5;
                }
            }
        }
    }

    int curVal = 10;
    if (current.getItemType() == ItemType::A) curVal = 12;
    else if (current.getItemType() == ItemType::B) curVal = 13;
    else if (current.getItemType() == ItemType::C) curVal = 14;

    if (!isFlash) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (TetrisBlock::getBlockData(current.getShape(), current.getAngle(), i, j) == 1) {
                    int by = current.getY() + i, bx = current.getX() + j;
                    if (by >= 0 && by < 21 && bx >= 0 && bx < 14) buffer[by][bx] = curVal;
                }
            }
        }
    }

    if (isFlash) {
        for (int row : flashRows) {
            for (int x = 1; x < 13; x++) {
                if (buffer[row][x] != 0) buffer[row][x] = 20;
            }
        }
    }

    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 14; x++) {
            if (buffer[y][x] != shadowBuffer[y][x]) {
                gotoxy(x * 2 + ab_x, y + ab_y);

                switch (buffer[y][x]) {
                case 0:  std::cout << "  "; break;
                case 1:  SetColor(borderColor); std::cout << "■"; break; // ★ 레벨별 벽 색상 적용 완료!
                case 7:  SetColor(GRAY);  std::cout << "■"; break;
                case 2: case 12: SetColor(RED); std::cout << "A "; break;
                case 3: case 13: SetColor(BLUE); std::cout << "B "; break;
                case 4: case 14: SetColor(YELLOW); std::cout << "C "; break;
                case 5:  SetColor(DARK_GRAY); std::cout << "□"; break;
                case 10: SetColor(current.getColor()); std::cout << "■"; break;
                case 20: SetColor(WHITE); std::cout << "▒"; break;
                default: SetColor(WHITE); std::cout << "■"; break;
                }
                shadowBuffer[y][x] = buffer[y][x];
            }
        }
    }
    SetColor(WHITE);
}