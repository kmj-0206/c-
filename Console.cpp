#include "Console.h"
#include "TetrisBlock.h"
#include "board.h"
#include "ItemEffect.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
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
//하나의 온전한 블록을 그림
void Console::drawBlock(const TetrisBlock& block, int startX, int startY, int mode)
{
    ItemEffect* effect = nullptr;
    static BombLineEffect effectA;
    static DoubleScoreEffect effectB;
    static StickBlockSupplyEffect effectC;

    int curColor = block.getColor();
    std::string blockMarker = "■";

    if (mode == 1) {
        curColor = BLACK;
        blockMarker = "  ";
    }
    else if (mode == 2) {
        curColor = DARK_GRAY;
        blockMarker = "□";
    }
    else {
        if (block.getItemType() == ItemType::A) { curColor = RED; effect = &effectA; }
        else if (block.getItemType() == ItemType::B) { curColor = BLUE; effect = &effectB; }
        else if (block.getItemType() == ItemType::C) { curColor = YELLOW; effect = &effectC; }

        if (effect != nullptr) {
            blockMarker = std::string(effect->name()) + " ";
        }
    }

    SetColor(curColor);

    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (TetrisBlock::getBlockData(block.getShape(), block.getAngle(), i, j) == 1) {
                if (startY + i < 0) continue;
                gotoxy(startX + j * 2, startY + i);
                std::cout << blockMarker;
            }
        }
    }
    SetColor(WHITE);
}

void Console::eraseBlock(const TetrisBlock& block)
{
    drawBlock(block, block.getX() * 2 + ab_x, block.getY() + ab_y, 1);
}

void Console::drawGhostBlock(const TetrisBlock& block, const Board& board)
{
    TetrisBlock ghost = block;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape())) {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }
    drawBlock(ghost, ghost.getX() * 2 + ab_x, ghost.getY() + ab_y, 2);
}
//UI 렌더링 함수들
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
    int my = -4, mx = 1, mShape = rand() % BLOCK_SHAPE_COUNT;
    ULONGLONG lastUpdate = GetTickCount64();

    while (!_kbhit())
    {
        ULONGLONG now = GetTickCount64();
        if (now - lastUpdate >= 100)
        {
            my++;
            bool coll = false;
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                    if (TetrisBlock::getBlockData(mShape, 0, i, j)) {
                        int by = my + i, bx = mx + j;
                        if (by >= 12 || bx < 0 || bx >= 6 || (by >= 0 && miniBoard[by][bx])) coll = true;
                    }
                }
            }

            if (coll) {
                my--;
                for (int i = 0; i < BLOCK_SIZE; i++) {
                    for (int j = 0; j < BLOCK_SIZE; j++) {
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
                my = -4; mx = rand() % 3; mShape = rand() % BLOCK_SHAPE_COUNT;
            }

            for (int r = 0; r < 12; r++) {
                gotoxy(30, 14 + r);
                SetColor(WHITE); std::cout << "│";
                for (int c = 0; c < 6; c++) {
                    bool isCur = false;
                    for (int i = 0; i < BLOCK_SIZE; i++) {
                        for (int j = 0; j < BLOCK_SIZE; j++) {
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
    gotoxy(baseX, baseY - 1);
    std::cout << "NEXT " << BlockQueue::getPreviewCnt();

    for (int n = 0; n < BlockQueue::getPreviewCnt(); n++)
    {
        int yOffset = baseY + n * BLOCK_SIZE;

        // 이전 잔상을 지우기 위한 공백 덮어쓰기
        for (int r = 0; r < BLOCK_SIZE; r++) {
            gotoxy(baseX, yOffset + r);
            std::cout << "        ";
        }

        if (n >= static_cast<int>(nextBlocks.size())) continue;

        // 길었던 아이템 색상 판별 및 2중 for문 렌더링 로직을 마스터 함수 단 1줄로 대체
        drawBlock(nextBlocks[n], baseX, yOffset);
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
// ────────────────────────────────────────────────────────
// 정적/동적 분리 캐시 데이터
// ────────────────────────────────────────────────────────
static int cachedBorderColor = Console::WHITE;
static TetrisBlock lastDrawnBlock;
static TetrisBlock lastDrawnGhost;
static bool hasLastDrawn = false;
void Console::clearDynamicCache() {
    hasLastDrawn = false;
}

void Console::eraseDynamic() {
    if (hasLastDrawn) {
        // 기존에 그려졌던 현재 블록과 고스트 블록의 흔적만 "  "로 지웁니다.
        eraseBlock(lastDrawnGhost);
        eraseBlock(lastDrawnBlock);
        hasLastDrawn = false;
    }
}

void Console::drawStatic(const Board& board, int level) {
    if (level == 1) cachedBorderColor = YELLOW;
    else if (level == 2) cachedBorderColor = DARK_YELLOW;
    else if (level == 3) cachedBorderColor = RED;
    else if (level >= 4) cachedBorderColor = DARK_RED;
    else cachedBorderColor = WHITE;

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            gotoxy(x * 2 + ab_x, y + ab_y);
            char cell = board.getBoardValue(y, x);

            if (cell == 1) { SetColor(cachedBorderColor); std::cout << "■"; }
            else if (cell == 7) { SetColor(GRAY); std::cout << "■"; }
            else if (cell == 2) { SetColor(RED); std::cout << "A "; }
            else if (cell == 3) { SetColor(BLUE); std::cout << "B "; }
            else if (cell == 4) { SetColor(YELLOW); std::cout << "C "; }
            else { std::cout << "  "; }
        }
    }
    SetColor(WHITE);
}

void Console::drawDynamic(const Board& board, const TetrisBlock& current) {
    TetrisBlock ghost = current;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape())) {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }

    //위치가 달라졌을 때만 고스트 블록 지우기
    if (hasLastDrawn) {
        if (lastDrawnGhost.getX() != ghost.getX() ||
            lastDrawnGhost.getY() != ghost.getY() ||
            lastDrawnGhost.getAngle() != ghost.getAngle() ||
            lastDrawnGhost.getShape() != ghost.getShape())
        {
            eraseBlock(lastDrawnGhost); // 다를 때만 빈칸으로 지움 (깜빡임 원인 제거)
        }

        // 현재 조종 중인 메인 블록은 위치가 매번 변함
        eraseBlock(lastDrawnBlock);
    }
    // 매 틱마다 덮어쓰기
    drawBlock(ghost, ghost.getX() * 2 + ab_x, ghost.getY() + ab_y, 2);
    drawBlock(current, current.getX() * 2 + ab_x, current.getY() + ab_y, 0);

    //  상태 저장
    lastDrawnBlock = current;
    lastDrawnGhost = ghost;
    hasLastDrawn = true;
}

void Console::drawFlash(const std::set<int>& rows, const Board& board, bool isFlash) {
    for (int row : rows) {
        for (int x = 1; x < BOARD_RIGHT_WALL; x++) {
            gotoxy(x * 2 + ab_x, row + ab_y);
            if (isFlash) {
                SetColor(WHITE);
                std::cout << "▒";
            }
            else {
                char cell = board.getBoardValue(row, x);
                if (cell == 1) { SetColor(cachedBorderColor); std::cout << "■"; }
                else if (cell == 7) { SetColor(GRAY); std::cout << "■"; }
                else if (cell == 2) { SetColor(RED); std::cout << "A "; }
                else if (cell == 3) { SetColor(BLUE); std::cout << "B "; }
                else if (cell == 4) { SetColor(YELLOW); std::cout << "C "; }
                else std::cout << "  ";
            }
        }
    }
    SetColor(WHITE);
}