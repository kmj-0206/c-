#pragma once
#include "board.h"
#include "BlockControl.h"
#include "Console.h"
#include "StageManager.h"
<<<<<<< HEAD
#include "RankingManager.h"
#include "ComboManager.h"
#include "DifficultyManager.h"
#include "BlockQueue.h"
#include "ItemEffectManager.h"
=======
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
#include <Windows.h>

class GameManager {
private:
<<<<<<< HEAD
=======
    // 싱글톤: 외부 생성 및 복사 방지
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    GameManager();
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

<<<<<<< HEAD
    Board board;
    StageManager stages;
    RankingManager rankingManager;
    ComboManager comboManager;
    DifficultyManager difficultyManager;
    BlockQueue blockQueue;
    ItemEffectManager itemEffectManager;

    int score;
    int lines;
=======
    // 멤버 변수들
    Board board;
    StageManager stages;
    int score;
    int lines;
    int level;
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    bool gameOver;
    TetrisBlock current;
    BlockControl controller;
    DWORD lastDrop;

<<<<<<< HEAD
    void handleInput();
    void updateGame();
    void fixCurrentBlock(DWORD now);
    void spawnNextBlock();
    void redrawScreen();

public:
    static GameManager& getInstance();
    void run();
};
=======
    // 핵심 내부 로직 메소드로 분리
    void handleInput();
    void updateGame();

public:
    // 유일한 인스턴스를 반환하는 static 메소드
    static GameManager& getInstance();

    // 게임 가동 엔진
    void run();
};
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
