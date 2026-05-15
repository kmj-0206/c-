#include "BlockControl.h"
BlockControl::BlockControl(const Board& board)
	:curBoard(&board),curControlBlock(nullptr)
{

}


BlockControl::~BlockControl()//메모리관리
{
}


using namespace Console;
bool BlockControl::move(MoveCommand cmd)
{
	BlockState proposed = curControlBlock->propose(cmd);
	if (canMoveTo(proposed)) {
		erase_block(*curControlBlock);
		curControlBlock->commit(proposed);
		show_block(*curControlBlock);
		return true;
	}
	return false;
}



void BlockControl::dropFull()
{
	erase_block(*curControlBlock);
	BlockState proposed = curControlBlock->propose(MoveCommand::DOWN);
	//아래로 내려갈 수 있으면 반복
	while (canMoveTo(proposed)) { 
		//가능하면 승인. 즉 위치이동
		curControlBlock->commit(proposed);
		//다음 정보 업데이트
		proposed = curControlBlock->propose(MoveCommand::DOWN);
	}
	show_block(*curControlBlock);

}


bool BlockControl::canMoveTo(const BlockState& state) const
{
	// 4x4 블록 입자를 하나씩 순회하며 검사
	for (int i = 0; i < 4; i++) // i는 블록 내부의 y (행)
	{
		for (int j = 0; j < 4; j++) // j는 블록 내부의 x (열)
		{
			// 현재 검사 중인 칸에 블록 데이터가 있는지 확인 (1이면 블록이 있는 것)
			if (curControlBlock->getBlock(curControlBlock->getShape(), state.angle, i, j) == 1)
			{
				// 블록 내부 인덱스(j, i)를 더해 보드 상의 절대 좌표 계산
				int boardX = state.x + j;
				int boardY = state.y + i;

				//1.가로충돌
				// 보드 너비 데이터를 getBoardWidth()로 가져온다고 가정
				if (boardX < 0 || boardX >= curBoard->getBoardWidth())
				{
					return false;
				}

				// 2. 바닥충돌
				// 보드 높이 데이터를 getBoardHeight()로 가져온다고 가정
				if (boardY >= curBoard->getBoardHeight())
				{
					return false;
				}

				// 3. 쌓인 블록과의 충돌 검사
				// boardY가 0보다 작을 때는(블록이 생성되어 내려오는 중) 체크 제외
				if (boardY >= 0)
				{
					// 특정 좌표의 보드 상태를 getBoardValue(y, x)로 가져온다고 가정
					if (curBoard->getBoardValue(boardY, boardX) == 1)
					{
						return false;
					}
				}
			}
		}
	}
	// 모든 검사를 통과하면 움직일 수 있음
	return true;
}

