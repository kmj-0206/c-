#pragma once
#include "TetrisBlock.h"
#include "StageManager.h"
#include "BlockFactory.h"
#include <vector>
using namespace std;

class BlockQueue
{
private:
    static const int PREVIEW_COUNT = 5;

    std::vector<TetrisBlock> nextBlocks;
    int forceStickCount;
    BlockFactory factory;

    // 블록 1개 생성 및 반환
    TetrisBlock createBlock(StageManager& stages, int level);
    // 프리뷰 큐 보충
    void fillPreview(StageManager& stages, int level);

public:
    // 기본 생성자
    BlockQueue();

    // 큐 및 프리뷰 초기화
    void init(StageManager& stages, int level);
    // 큐에서 다음 블록 꺼내고 프리뷰 채우기
    TetrisBlock pop(StageManager& stages, int level);

    // 다음 n개의 블록을 I 블록으로 강제 스폰 예약
    void forceNextStickBlocks(int count);

    // 프리뷰 블록 목록 반환
    const std::vector<TetrisBlock>& preview() const;
    static int getPreviewCnt() { return PREVIEW_COUNT; }
};