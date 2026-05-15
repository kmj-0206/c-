#include "Console.h"
#include "TetrisBlock.h"//block 객체 생성 위해서
#include <iostream>
void Console::gotoxy(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}

void Console::SetColor(int color) {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

void Console::clear()
{
	system("cls");
}

void Console::show_block(const TetrisBlock& block)
{
	using namespace std;
	SetColor(block.getColor());
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if ((j + block.getY() < 0))
					continue;

				if (block.getBlock(block.getShape(), block.getAngle(),j,i) == 1)
				{
					gotoxy((i + block.getX()) * 2 + ab_x, j + block.getY() + ab_y);
					printf("■"); //cout보다 빨라서 그냥 이용
				}
			}
		}
	
}
void Console::erase_block(const TetrisBlock& block)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.getBlock(block.getShape(),block.getAngle(),j,i) == 1)
			{
				gotoxy((i + block.getX()) * 2 + ab_x, j + block.getY() + ab_y);
				printf("  ");
			}
		}
	}
}