#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
class TetrisBlock;//블록에서도 색상 정보때문에 얘가 필요해서, 전방선언

namespace Console {
	//화면중 블럭이 나타나는 좌표의 절대위치
	constexpr int ab_x = 5;  // 절대 위치 X
	constexpr int ab_y = 1;  // 절대 위치 Y
    // 객체 생성 없이 Console::gotoxy(...) 형태로 호출
    void gotoxy(int x, int y);
    void SetColor(int color);
    void clear(); // system("cls") 대신 사용할 수도 있음
	void show_block(const TetrisBlock& block);
	void erase_block(const TetrisBlock& block);
	enum Color {
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
};

#endif