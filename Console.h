#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

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

    void drawBoard(const Board& board);

    void drawInfo(int score, int lines, int level);

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