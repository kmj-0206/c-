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

    void drawBoard(const Board& board);
    void drawInfo(int score, int lines, int level, int comboMultiplier, int difficulty);
    void drawNextBlocks(const std::vector<TetrisBlock>& nextBlocks);
    void drawRankings(const std::vector<int>& ranks);
    void drawGameOver();

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
