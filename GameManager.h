#pragma once
#include "board.h"
#include "BlockControl.h"
#include "Console.h"
#include "StageManager.h"
#include <Windows.h>

class GameManager {
private:
    // 싱글톤: 외부 생성 및 복사 방지
    GameManager();
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // 멤버 변수들
    Board board;
    StageManager stages;
    int score;
    int lines;
    int level;
    bool gameOver;
    TetrisBlock current;
    BlockControl controller;
    DWORD lastDrop;

    // 핵심 내부 로직 메소드로 분리
    void handleInput();
    void updateGame();

public:
    // 유일한 인스턴스를 반환하는 static 메소드
    static GameManager& getInstance();

    // 게임 가동 엔진
    void run();
};