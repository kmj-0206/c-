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
    GameState currentState = GameState::TITLE; //처음 state는 title
    bool isRunning = true;
    rankingManager.load(); // 랭킹 정보는 처음에 한 번 로드

    while (isRunning) {
        switch (currentState) {
        case GameState::TITLE:
            Console::drawTitle();
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
            board.init();
            blockQueue.init(stages, difficultyManager.getLevel());
            current = blockQueue.pop(stages, difficultyManager.getLevel());
            controller.setCurrentBlock(current);

            score = 0;
            lines = 0;
            gameOver = false;
            isGameClear = false; // 플래그 초기화

            Console::clear();
            Console::hideCursor();
            Console::clearShadowBuffer();

            drawUI();
            redrawScreen();
            lastDrop = GetTickCount64();

            while (!gameOver) {
                handleInput();
                updateGame();
                redrawScreen();
                Sleep(15);
            }

            rankingManager.saveScore(score);
            redrawScreen();

            // 게임 오버인지, 클리어인지에 따라 다른 연출
            if (isGameClear) {
                Console::drawGameClear();
            }
            else {
                Console::drawGameOver();
            }

            std::cout << "\n\n\tPress any key to view rankings...";
            _getch();
            currentState = GameState::RANKING;
            break;

        case GameState::RANKING:
            Console::clear();
            Console::drawFullRankings(rankingManager.getRank()); // 풀 랭킹창 호출로 변경

            // 8위 점수와 겹치지 않도록 Y좌표를 20에서 27로  내림
            Console::gotoxy(30, 27);
            std::cout << "[1] Main Menu     [ESC] Exit Game";

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
    Console::gotoxy(0, 25);
}

void GameManager::handleInput() {
    if (_kbhit()) {
        int key = _getch();

        if (key == 27) {
            gameOver = true;
            return;
        }

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 75: controller.move(MoveCommand::LEFT);   break;
            case 77: controller.move(MoveCommand::RIGHT);  break;
            case 80: controller.move(MoveCommand::DOWN);   break;
            case 72: controller.move(MoveCommand::ROTATE); break;
            }
        }
        else if (key == ' ') {
            controller.dropFull();
            lastDrop = 0;
        }
    }
}

void GameManager::updateGame() {
    ULONGLONG now = GetTickCount64();
    int speed = difficultyManager.getCurrentSpeed(score, stages);

    if (now - lastDrop >= static_cast<ULONGLONG>(speed)) {
        bool moved = controller.move(MoveCommand::DOWN);

        if (!moved) {
            fixCurrentBlock(now);

            // 블록을 합치는 과정에서 클리어나 오버 판정이 나면 다음 블록을 생성하지 않음
            if (!gameOver) {
                spawnNextBlock();
                drawUI();
            }
        }
        lastDrop = now;
    }
}

void GameManager::fixCurrentBlock(ULONGLONG now)
{
    if (gameRule.isGameOverOnMerge(current)) {
        gameOver = true;
        return;
    }
    board.merge(current);

    ClearResult clearResult = board.checkClearLines();

    // 2. 라인 클리어 애니메이션 처리
    if (!clearResult.removedRows.empty()) {
        for (int i = 0; i < 4; i++) {
            Console::drawGameField(board, current, difficultyManager.getLevel(), clearResult.removedRows, i % 2 == 0);
            Sleep(80);
        }
        board.removeLines(clearResult.removedRows);
    }

    int combo = comboManager.updateByClear(clearResult.fullLines);

    if (clearResult.fullLines > 0) {
        int gained = clearResult.fullLines * (100 + difficultyManager.getLevel() * 10);
        gained *= combo;
        gained = itemEffectManager.applyAfterCalculateScore(gained, clearResult);

        score += gained;
        lines += clearResult.fullLines;

        itemEffectManager.applyBeforeRemoveLines(clearResult, blockQueue);

        if (difficultyManager.updateLevel(score, lines, stages)) {
            gameOver = true;
            isGameClear = true;
        }
    }
}

void GameManager::spawnNextBlock()
{
    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    if (gameRule.isGameOverOnSpawn(controller, current)) {
        gameOver = true;
        return;
    }
}

void GameManager::redrawScreen()
{
    using namespace Console;
    
    
    drawGameField(board, current, difficultyManager.getLevel());
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