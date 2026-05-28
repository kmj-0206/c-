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

    int score;
    int lines;
    bool gameOver;
    TetrisBlock current;
    BlockControl controller;
    DWORD lastDrop;

    void handleInput();
    void updateGame();
    void fixCurrentBlock(DWORD now);
    void spawnNextBlock();
    void redrawScreen();

public:
    static GameManager& getInstance();
    void run();
};
