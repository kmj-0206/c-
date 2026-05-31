#pragma once
#include "BlockControl.h"
#include "TetrisBlock.h"
class GameRule
{
public://Lock-out: 블록이 천장(y < 0)에 닿은 채로 고정되었는지
	bool isGameOverOnMerge(const TetrisBlock& block) const;
	//새 블록이 생성되자마자 기존 블록과 겹치는지
	bool isGameOverOnSpawn(const BlockControl& controller, const TetrisBlock& block) const;

};

