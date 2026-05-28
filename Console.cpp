#include "Console.h"
#include "TetrisBlock.h"
#include "board.h"
#include <iostream>
#include <string>

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

void Console::show_block(const TetrisBlock& block)
{
    SetColor(block.getColor());

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(block.getShape(), block.getAngle(), i, j) == 1)
            {
                if (block.getY() + i < 0) continue;
                int drawX = (block.getX() + j) * 2 + ab_x;
                int drawY = block.getY() + i + ab_y;
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
            if (TetrisBlock::getBlockData(block.getShape(), block.getAngle(), i, j) == 1)
            {
                if (block.getY() + i < 0) continue;
                int drawX = (block.getX() + j) * 2 + ab_x;
                int drawY = block.getY() + i + ab_y;
                gotoxy(drawX, drawY);
                std::cout << "  ";
            }
        }
    }
}

void Console::drawGhostBlock(const TetrisBlock& block, const Board& board)
{
    TetrisBlock ghost = block;
    BlockState next = ghost.propose(MoveCommand::DOWN);
    while (!board.isCollision(next, ghost.getShape()))
    {
        ghost.commit(next);
        next = ghost.propose(MoveCommand::DOWN);
    }

    SetColor(DARK_GRAY);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (TetrisBlock::getBlockData(ghost.getShape(), ghost.getAngle(), i, j) == 1)
            {
                if (ghost.getY() + i < 0) continue;
                gotoxy((ghost.getX() + j) * 2 + ab_x, ghost.getY() + i + ab_y);
                std::cout << "□";
            }
        }
    }
    SetColor(WHITE);
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

void Console::drawInfo(int score, int lines, int level, int comboMultiplier, int difficulty)
{
    gotoxy(40, 3); std::cout << "Score : " << score << "      ";
    gotoxy(40, 5); std::cout << "Lines : " << lines << "      ";
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
        for (int r = 0; r < 4; r++)
        {
            gotoxy(baseX, yOffset + r);
            std::cout << "        ";
        }

        if (n >= static_cast<int>(nextBlocks.size())) continue;
        const TetrisBlock& block = nextBlocks[n];
        SetColor(block.getColor());
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (TetrisBlock::getBlockData(block.getShape(), 0, i, j) == 1)
                {
                    gotoxy(baseX + j * 2, yOffset + i);
                    std::cout << "■";
                }
            }
        }
        SetColor(WHITE);
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
