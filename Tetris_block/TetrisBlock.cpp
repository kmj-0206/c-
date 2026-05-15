#include "TetrisBlock.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

enum {
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};


TetrisBlock::TetrisBlock(int stick_rate)
	:x(ab_x),y(ab_y),stick_rate(stick_rate),angle(0)
{
	
	int i=rand()&100;
	if (i < stick_rate) {
		shape = 0;
	}
	else {
		shape = (rand() % 6) + 1;
	}

	switch (shape)
	{
	case 0: color = RED;
		break;
	case 1: color = BLUE;
		break;
	case 2: color = SKY_BLUE;
		break;
	case 3: color = WHITE; 
		break;
	case 4: color = YELLOW;
		break;
	case 5: color = VOILET;
		break;
	case 6: color = GREEN;
		break;
	}
	SetColor(color);

}

void TetrisBlock::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}

void TetrisBlock::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

void TetrisBlock::show_block()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("■");
			}
		}
	}

}

void TetrisBlock::erase_block()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");
			}
		}
	}
}

void TetrisBlock::move_left()
{
	if (x > 1) {
		erase_block();
		x--;
		show_block();
	}
}

void TetrisBlock::move_right()
{
	erase_block();
	x++;
	show_block();
}

void TetrisBlock::move_down()
{
	erase_block();
	x--;
	show_block();
}

void TetrisBlock::rotate()
{
	erase_block();
	angle = (angle + 1) % 4;
	show_block();
}
