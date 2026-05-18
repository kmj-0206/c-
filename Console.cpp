#include "Console.h"
#include "TetrisBlock.h"
#include "board.h"
#include <iostream>

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
    static HANDLE std_output_handle =
        GetStdHandle(STD_OUTPUT_HANDLE);

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

void Console::show_block(const TetrisBlock& block)
{
    SetColor(block.getColor());

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block.getBlock(
                block.getShape(),
                block.getAngle(),
                i,
                j) == 1)
            {
                int drawX =
                    (block.getX() + j) * 2 + ab_x;

                int drawY =
                    block.getY() + i + ab_y;

                gotoxy(drawX, drawY);

                std::cout << "■";
            }
        }
    }

    SetColor(WHITE);
}

void Console::erase_block(const TetrisBlock& block)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block.getBlock(
                block.getShape(),
                block.getAngle(),
                i,
                j) == 1)
            {
                int drawX =
                    (block.getX() + j) * 2 + ab_x;

                int drawY =
                    block.getY() + i + ab_y;

                gotoxy(drawX, drawY);

                std::cout << "  ";
            }
        }
    }
}

void Console::drawBoard(const Board& board)
{
    for (int y = 0; y < board.getBoardHeight(); y++)
    {
        for (int x = 0; x < board.getBoardWidth(); x++)
        {
            gotoxy(x * 2 + ab_x, y + ab_y);

            if (board.getBoardValue(y, x))
            {
                std::cout << "■";
            }
            else
            {
                std::cout << "  ";
            }
        }
    }
}

void Console::drawInfo(int score, int lines, int level)
{
    gotoxy(40, 3);
    std::cout << "Score : " << score << "   ";

    gotoxy(40, 5);
    std::cout << "Lines : " << lines << "   ";

    gotoxy(40, 7);
    std::cout << "Level : " << level + 1 << "   ";
}

void Console::drawGameOver()
{
    gotoxy(40, 12);
    std::cout << "GAME OVER";
}