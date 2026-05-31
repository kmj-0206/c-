#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <vector>

class TetrisBlock;
class Board;

namespace Console {

    constexpr int ab_x = 5;
    constexpr int ab_y = 1;

    void gotoxy(int x, int y);
    void SetColor(int color);
    void clear();
    void hideCursor();

    void show_block(const TetrisBlock& block);
    void erase_block(const TetrisBlock& block);
    void drawGhostBlock(const TetrisBlock& block, const Board& board);
    //렌더링 중복 제거를 위한 마스터 함수
    void drawBlockShape(int shape, int angle, int startX, int startY, int color, int mode);

    void drawTitle();
    void drawBoard(const Board& board);
    void drawInfo(int score, int lines, int level, int comboMultiplier, int difficulty);
    void drawNextBlocks(const std::vector<TetrisBlock>& nextBlocks);
    void drawRankings(const std::vector<int>& ranks);
    void drawGameOver(); //게임오버 UI
    void drawGameClear(); // 게임 클리어 UI

    void drawGameField(const Board& board, const TetrisBlock& current);

    void initRenderBuffer(char buffer[21][14], const Board& board);
    void applyBlocksToBuffer(char buffer[21][14], const Board& board, const TetrisBlock& current);
    void renderGameBuffer(const char buffer[21][14], int currentBlockColor);
    void clearShadowBuffer(); //  렌더링 찌꺼기 방지용

    enum Color {
        BLACK,
        DARK_BLUE,
        DARK_GREEN,
        DARK_SKY_BLUE,
        DARK_RED,
        DARK_VOILET,
        DARK_YELLOW,
        GRAY,
        DARK_GRAY,
        BLUE,
        GREEN,
        SKY_BLUE,
        RED,
        VOILET,
        YELLOW,
        WHITE,
    };
}

#endif
