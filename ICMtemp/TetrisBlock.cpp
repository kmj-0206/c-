#include "TetrisBlock.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

// 블록 객체의 초기 좌표 및 모양을 설정함
TetrisBlock::TetrisBlock(int stick_rate)
	:x(ab_x), y(ab_y), stick_rate(stick_rate), angle(0)
{
	int i = rand() % 100;
	if (i < stick_rate) {
		shape = 0;
	}
	else {
		shape = (rand() % 6) + 1;
	}
	using namespace Console;
	switch (shape)// 블록의 모양(shape) 데이터에 따라 고유한 색상 코드를 지정
	{
	case 0: color = RED; break;
	case 1: color = BLUE; break;
	case 2: color = SKY_BLUE; break;
	case 3: color = WHITE; break;
	case 4: color = YELLOW; break;
	case 5: color = VOILET; break;
	case 6: color = GREEN; break;
	}
}



// 현재 좌표를 건드리지 않고 명령(cmd)에 따른 예상 좌표와 각도를 계산하여 반환함
BlockState TetrisBlock::propose(MoveCommand cmd) const
{
	BlockState next = { x, y, angle };

	switch (cmd)
	{
	case MoveCommand::LEFT:
		move_left(next);
		break;
	case MoveCommand::RIGHT:
		move_right(next);
		break;
	case MoveCommand::DOWN:
		move_down(next);
		break;
	case MoveCommand::ROTATE:
		move_rotate(next);
		break;
	}
	return next;
}

// 컨트롤러로부터 검증받은 새로운 상태를 블록의 실제 좌표 및 각도로 확정함
void TetrisBlock::commit(const BlockState& state)
{
	this->x = state.x;
	this->y = state.y;
	this->angle = state.angle;
}

void TetrisBlock::move_left(BlockState& state) const
{
	state.x--;
}

void TetrisBlock::move_right(BlockState& state) const
{
	state.x++;
}

void TetrisBlock::move_down(BlockState& state) const
{
	state.y++;
}

void TetrisBlock::move_rotate(BlockState& state) const
{
	state.angle = (angle + 1) % 4;
}
