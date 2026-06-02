#pragma once
#include "board.h"
#include "BlockControl.h"
#include "Console.h"
#include "StageManager.h"
#include "RankingManager.h"
#include "ComboManager.h"
#include "DifficultyManager.h"
#include "BlockQueue.h"
#include "ItemEffectManager.h"
#include <Windows.h>
#include "GameRule.h"
enum class GameState {
    TITLE = 1,
    DIFFICULTY_SELECT =2,
    IN_GAME = 3,
    RANKING = 4,
    EXIT
};
class GameManager {
private:
    GameManager();
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    Board board;
    StageManager stages;
    RankingManager rankingManager;
    ComboManager comboManager;
    DifficultyManager difficultyManager;
    BlockQueue blockQueue;
    ItemEffectManager itemEffectManager;
    GameRule gameRule;

    int score;
    int lines;
    bool gameOver;
    bool isGameClear; // 게임 클리어 상태 변수 추가
    TetrisBlock current;
    BlockControl controller;
    ULONGLONG lastDrop;

    void resetGame(); //미사용 함수
    void handleInput();
    void updateGame();
    void fixCurrentBlock(ULONGLONG now);
    void processLineClear(ClearResult& clearResult); // 미사용 함수
    void spawnNextBlock();
    void redrawScreen();
    void drawUI();
public:
    static GameManager& getInstance();
    void run();
};
