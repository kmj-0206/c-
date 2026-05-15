
#pragma once
#include "Console.h"

// 블록의 가상 상태를 담는 바구니
struct BlockState {
	int x, y, angle;
};

// 블록에게 내리는 명령 종류
enum class MoveCommand {
	LEFT, RIGHT, DOWN, ROTATE
};

class TetrisBlock
{
private:
	static const char block[7][4][4][4];
	int shape;
	int angle;
	int x;
	int y;
	const int ab_x = 5;
	const int ab_y = 1;
	int stick_rate;
	int color;

	void move_left(BlockState& state) const;
	void move_right(BlockState& state) const;
	void move_down(BlockState& state) const;
	void move_rotate(BlockState& state) const;
public:
	TetrisBlock(int stick_rate);

	// 컨트롤러의 요청에 따라 미래의 상태를 계산하여 컨트롤러에 제안함
	BlockState propose(MoveCommand cmd) const;

	// 컨트롤러가 승인한 상태를 실제 블록 데이터에 반영함
	void commit(const BlockState& state);


	// Getter 함수
	int getX() const { return x; }
	int getY() const { return y; }
	int getAngle() const { return angle; }
	int getShape() const { return shape; }
	int getColor() const { return color; }
	char getBlock(int s, int a, int y, int x) const { return block[s][a][y][x]; }
};