#pragma once
class TetrisBlock
{
private:
	static const char block[7][4][4][4];
	int shape;
	int angle;
	int x;
	int y;
	const int ab_x=5;
	const int ab_y=1;
	int stick_rate;
	int color;
public:
	//생성자
	TetrisBlock(int stick_rate);

	void gotoxy(int x, int y);
	void SetColor(int color);

	//show & erase
	void show_block();
	void erase_block();

	//블록 이동 로직
	//단순히 이동만 구현했습니다. 블록이 닿았는지 확인은 보드에서 해야될 것 같아요.
	void move_left();   //왼쪽 화살표
	void move_right();  //오른쪽 화살표
	void move_down();	//아래 화살표
	void rotate();		//위 화살표

	//Getter 함수
	int getX() { return x; }
	int getY() { return y; }
	int getAngle() { return angle; }
	int getShape() { return shape; }

	 


};

