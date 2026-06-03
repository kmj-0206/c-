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

    // 게임 데이터 초기화 및 게임 시작 준비
    void resetGame();
    // 사용자 키보드 입력 처리
    bool handleInput();
    // 타이머 틱에 따른 게임 논리 갱신
    bool updateGame();
    // 바닥에 닿은 블록 병합 및 라인 정리 실행
    void fixCurrentBlock(ULONGLONG now);
    // 큐에서 다음 블록 꺼내고 스폰 오버 검사
    void spawnNextBlock();
   
    // 게임 UI(정보, 넥스트, 랭킹) 화면 출력
    void drawUI();
public:
    // 게임 매니저 싱글톤 인스턴스 반환
    static GameManager& getInstance();
    // 게임 전체 메인 구동 루프
    void run();
};