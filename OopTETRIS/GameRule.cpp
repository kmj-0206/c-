#include "GameRule.h"
bool GameRule::isGameOverOnMerge(const TetrisBlock& block) const
{
    // y좌표가 0보다 작으면 화면 밖에서 굳은 것이므로 게임 오버
    return block.getY() < 0;
}

bool GameRule::isGameOverOnSpawn(const BlockControl& controller, const TetrisBlock& block) const
{
    BlockState state = { block.getX(), block.getY(), block.getAngle() };

    // 해당 위치로 이동할 수 없다면(겹친다면) 게임 오버
    return !controller.canMoveTo(state);
}