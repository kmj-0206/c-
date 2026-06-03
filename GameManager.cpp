#include "GameManager.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager()
    : board(),
    stages(5),
    rankingManager("rank.txt"),
    comboManager(),
    difficultyManager(),
    blockQueue(),
    itemEffectManager(),
    score(0),
    lines(0),
    gameOver(false),
    current(20),
    controller(board),
    isGameClear(false),
    lastDrop(0)
{
    controller.setCurrentBlock(current);
}

void GameManager::run() {
    using namespace Console;
    GameState currentState = GameState::TITLE; //처음 state는 title
    bool isRunning = true;
    rankingManager.load(); // 랭킹 정보는 처음에 한 번 로드

    while (isRunning) {
        switch (currentState) {
        case GameState::TITLE:
            drawTitle();
            currentState = GameState::DIFFICULTY_SELECT;
            break;

        case GameState::DIFFICULTY_SELECT:
            // int 반환값을 받아 랭킹으로 갈지, 인게임으로 갈지 결정
        {
            int selection = difficultyManager.select(); //case문 안에 있는 지역변수는 scope 확실히 안 해주면 에러남
            if (selection == 4) {
                currentState = GameState::RANKING;
            }
            else {
                currentState = GameState::IN_GAME;
            }
            break;
        }

        case GameState::IN_GAME:
            // 인게임 진입 시 보드 및 큐 초기화
            resetGame();

            while (!gameOver) {
                // 키 입력이나 타이머에 의한 변화가 발생했을 때만 동적 그리기 호출
                bool inputRedraw = handleInput();
                bool timeRedraw = updateGame();

                if (inputRedraw || timeRedraw) {
                    drawDynamic(board, current);
                }
                Sleep(15);
            }

            rankingManager.saveScore(score);
            drawDynamic(board, current);

            // 게임 오버인지, 클리어인지에 따라 다른 연출
            if (isGameClear) {
                drawGameClear();
            }
            else {
                drawGameOver();
            }

            std::cout << "\n\n\tPress any key to view rankings...";
            _getch();
            currentState = GameState::RANKING;
            break;

        case GameState::RANKING:
            clear();
            drawFullRankings(rankingManager.getRank()); // 풀 랭킹창 호출로 변경

            // 8위 점수와 겹치지 않도록 Y좌표를 20에서 27로  내림
            gotoxy(30, 27);
            cout << "[1] Main Menu     [ESC] Exit Game";

            while (_kbhit()) _getch();
            while (true) {
                int key = _getch();
                if (key == '1') {
                    currentState = GameState::TITLE;
                    break;
                }
                if (key == 27) {
                    currentState = GameState::EXIT;
                    break;
                }
            }
            break;

        case GameState::EXIT:
            isRunning = false;
            break;
        }
    }
    gotoxy(0, 25);
}
//run함수만 호출하긴 하는데, 그냥, 나중에 수정하기 좋으라고 이렇게 함
void GameManager::resetGame()
{
    board.init();
    blockQueue.init(stages, difficultyManager.getLevel());
    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    score = 0;
    lines = 0;
    gameOver = false;
    isGameClear = false;

    Console::clear();
    Console::hideCursor();
    Console::clearDynamicCache(); // 이전 판의 추적 데이터 초기화

    drawUI();
    // 시작 시 보드, 벽 색상 초기화를 위해 정적 대상을 1회 출력
    Console::drawStatic(board, difficultyManager.getLevel());
    Console::drawDynamic(board, current);
    lastDrop = GetTickCount64();
}

bool GameManager::handleInput() {
    if (!_kbhit()) return false;

    int key = _getch();

    if (key == 27) {
        gameOver = true;
        return false;
    }

    if (key == 224) {
        key = _getch();
        switch (key) {
            // controller.move가 성공적으로 이동했을 때만 true를 반환하여 렌더링을 유도
        case 75: return controller.move(MoveCommand::LEFT);
        case 77: return controller.move(MoveCommand::RIGHT);
        case 80: return controller.move(MoveCommand::DOWN);
        case 72: return controller.move(MoveCommand::ROTATE);
        }
    }
    else if (key == ' ') {
        controller.dropFull();
        lastDrop = 0; // 즉시 바닥에 고정되도록 타이머 리셋
        return true;  // 스페이스바를 누르면 무조건 화면 갱신 필요
    }
    return false;
}
//game logic update
bool GameManager::updateGame() {
    ULONGLONG now = GetTickCount64();
    int speed = difficultyManager.getCurrentSpeed(score, stages);

    if (now - lastDrop >= static_cast<ULONGLONG>(speed)) {
        bool moved = controller.move(MoveCommand::DOWN);

        if (!moved) {
            fixCurrentBlock(now);

            if (!gameOver) {
                spawnNextBlock();
                drawUI();
            }
        }
        lastDrop = now;
        return true; // 하강이나 블록 스폰으로 인해 화면 변화 발생
    }
    return false;
}

void GameManager::fixCurrentBlock(ULONGLONG now)
{
    // 보드와 겹치기 '직전'에 화면에 남아있는 동적 객체를 강제로 싹 지웁니다.
    Console::eraseDynamic();
    Console::clearDynamicCache(); // 다음 프레임부터 새로 추적 시작

    if (gameRule.isGameOverOnMerge(current)) {
        gameOver = true;
        return;
    }
    board.merge(current);

    ClearResult clearResult = board.checkClearLines();
    itemEffectManager.applyBeforeRemoveLines(clearResult, blockQueue);

    if (!clearResult.removedRows.empty()) {
        // 이펙트 발동 전 합쳐진 보드의 데이터를 1회 갱신
        Console::drawStatic(board, difficultyManager.getLevel());

        for (int i = 0; i < 4; i++) {
            Console::drawFlash(clearResult.removedRows, board, i % 2 == 0);
            Sleep(80);
        }
        board.removeLines(clearResult.removedRows);
    }

    int combo = comboManager.updateByClear(clearResult.fullLines);

    if (clearResult.fullLines > 0) {
        int gained = clearResult.fullLines * (100 + difficultyManager.getLevel() * 10);
        gained *= combo;
        gained = itemEffectManager.applyAfterCalculateScore(gained, clearResult);

        score += gained * difficultyManager.getDifficulty();
        lines += clearResult.fullLines;

        if (difficultyManager.updateLevel(score, lines, stages)) {
            gameOver = true;
            isGameClear = true;
        }
    }

    // 병합/삭제 후 보드 데이터가 고정되었으므로 정적 레이어 최종 반영
    Console::drawStatic(board, difficultyManager.getLevel());
}

void GameManager::spawnNextBlock()
{
    Console::clearDynamicCache();

    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    if (gameRule.isGameOverOnSpawn(controller, current)) {
        gameOver = true;
        return;
    }
}


void GameManager::drawUI()
{
    using namespace Console;
    drawInfo(
        score,
        difficultyManager.getRemainingLines(lines, stages),
        difficultyManager.getLevel(),
        comboManager.getMultiplier(),
        difficultyManager.getDifficulty()
    );
    drawNextBlocks(blockQueue.preview());
    drawSideRankings(rankingManager.getRank()); // 사이드 랭킹으로 이름 변경
}