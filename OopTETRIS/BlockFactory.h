#pragma once
#include "TetrisBlock.h"
#include "StageManager.h"

// ------------------------------------------------------------
// BlockFactory
// ------------------------------------------------------------
// 블록 생성 책임만 담당하는 클래스.
// 기존에는 BlockQueue가 "큐 관리"와 "블록 생성"을 동시에 담당했다.
// 이 클래스를 분리하면 BlockQueue는 다음 블록 목록 관리에만 집중할 수 있다.
class BlockFactory
{
public:
    // 현재 스테이지 정보를 이용해 일반 랜덤 블록을 생성한다.
    TetrisBlock createRandomBlock(StageManager& stages, int level) const;

    // 아이템 C 효과에서 사용하는 긴 막대 블록 강제 생성 함수.
    TetrisBlock createStickBlock(StageManager& stages, int level) const;
};
