#pragma once
#include "TetrisBlock.h"

class Board; //나중에 헤더파일 받아서 사용

class BlockControl
{
private:
	TetrisBlock* curControlBlock;//블록은 여기서 수정해야함
	const Board* curBoard; //보드는 변경 가능. 그런데 보드의 데이터는 수정 불가
	
public:
	BlockControl()=delete; //생성 시점: 게임 들어간 후.  그 후엔 데이터만 변경
	BlockControl(const Board& board); //보드는 반드시 필요함. 블록은 하나의 컨트롤러에서 계속 변하고. 
	~BlockControl();
	//수치변경을 블록에 해두고, 실행을 여기서(출력, 충돌 감지 포함.)
	//return 성공여부
	bool move(MoveCommand cmd);
	
	//return 성공여부
	void dropFull(); // 스페이스바: 바닥까지 한 번에 이동

	//이동 가능 여부는 보드의 데이터 받아와서 여기서 판정
	//게임오버 확인 여부는 컨트롤러에 넣을지 고민 좀 하고, 추후에 결정. 이동 로직이 이곳에 있어서 아마 넣긴 할 듯.
	bool canMoveTo(const BlockState& proposedState) const; 

	
	TetrisBlock* getCurrentBlock() { return curControlBlock; }
	//메인함수에서 블록 바꿀 때(또는 다음 블록으로 전환시) 사용
	void setCurrentBlock(TetrisBlock& block) { this->curControlBlock = &block; }
	//작동순서. canmove->erase->move->draw꼴.
};