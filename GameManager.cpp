#include "GameManager.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

GameManager& GameManager::getInstance() {
<<<<<<< HEAD
=======
   //싱글톤 디자인
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    static GameManager instance;
    return instance;
}

GameManager::GameManager()
    : board(),
    stages(5),
<<<<<<< HEAD
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
    lastDrop(0)
{
=======
    score(0),
    lines(0),
    level(0),
    gameOver(false),
    current(stages[0]->getStick_rate()), // 초기 레벨 0의 데이터 활용
    controller(board),
    lastDrop(0)
{
    // 컨트롤러에 첫 블록 주입
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    controller.setCurrentBlock(current);
}

void GameManager::run() {
<<<<<<< HEAD
    difficultyManager.select();
    rankingManager.load();

    board.init();
    blockQueue.init(stages, difficultyManager.getLevel());
    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    Console::clear();
    Console::hideCursor();
    redrawScreen();

=======
    // 게임 시작 전 초기 셋팅
    board.init();
    Console::clear();
    Console::hideCursor();
    Console::drawBoard(board);
    Console::drawInfo(score, lines, level);

    // 첫 시작 시 충돌 여부 확인 (게임오버 조건)
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
        gameOver = true;
    }

<<<<<<< HEAD
    lastDrop = GetTickCount64();

    while (!gameOver) {
        handleInput();
        updateGame();
        redrawScreen();
        Sleep(15);
    }

    rankingManager.saveScore(score);
    redrawScreen();
=======
    Console::show_block(current);
    lastDrop = GetTickCount64();

    // 메인 게임 루프 실행
    while (!gameOver) {
        handleInput();
        updateGame();
        Sleep(15);
    }

    // 게임 종료 연출
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
    Console::drawGameOver();
    Console::gotoxy(0, 25);
}

void GameManager::handleInput() {
    if (_kbhit()) {
        int key = _getch();

<<<<<<< HEAD
        if (key == 27) {
=======
        if (key == 27) { // ESC 키 누르면 즉시 종료
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
            gameOver = true;
            return;
        }

<<<<<<< HEAD
        if (key == 224) {
=======
        if (key == 224) { // 화살표 특수키 처리
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
            key = _getch();
            switch (key) {
            case 75: controller.move(MoveCommand::LEFT);   break;
            case 77: controller.move(MoveCommand::RIGHT);  break;
            case 80: controller.move(MoveCommand::DOWN);   break;
            case 72: controller.move(MoveCommand::ROTATE); break;
            }
        }
<<<<<<< HEAD
        else if (key == ' ') {
=======
        else if (key == ' ') { // 스페이스바 처리
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
            controller.dropFull();
            lastDrop = 0;
        }
    }
}

void GameManager::updateGame() {
    DWORD now = GetTickCount64();
<<<<<<< HEAD
    int speed = difficultyManager.getCurrentSpeed(score, stages);

    if (now - lastDrop >= static_cast<DWORD>(speed)) {
        bool moved = controller.move(MoveCommand::DOWN);

        if (!moved) {
            fixCurrentBlock(now);
            spawnNextBlock();
=======

    // 블록 자동 낙하 타이머 시스템
    if (now - lastDrop >= static_cast<DWORD>(stages[level]->getSpeed())) {
        bool moved = controller.move(MoveCommand::DOWN);

        // 아래로 움직이지 못했다면 블록 고정 및 라인 클리어 진행
        if (!moved) {
            board.merge(current);
            board.clearFullLines(score, lines, level);

            // 레벨 및 스테이지 계산
            int newLevel = lines / stages[level]->getClear_line();
            if (newLevel >= stages.getCount()) {
                newLevel = stages.getCount() - 1;
            }
            level = newLevel;

            // UI 스크린 업데이트
            Console::drawBoard(board);
            Console::drawInfo(score, lines, level);

            // 다음 새로운 블록 생성 및 컨트롤러에 갱신
            current = TetrisBlock(stages[level]->getStick_rate());
            controller.setCurrentBlock(current);

            // 블록 생성하자마자 충돌하면 게임오버
            if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
                gameOver = true;
                return;
            }

            Console::show_block(current);
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
        }

        lastDrop = now;
    }
<<<<<<< HEAD
}

void GameManager::fixCurrentBlock(DWORD now)
{
    board.merge(current);

    ClearResult clearResult = board.clearFullLines();
    int combo = comboManager.updateByClear(clearResult.fullLines, now);

    if (clearResult.fullLines > 0) {
        int gained = clearResult.fullLines * (100 + difficultyManager.getLevel() * 10);
        gained *= combo;
        gained = itemEffectManager.applyScoreEffect(gained, clearResult);

        score += gained;
        lines += clearResult.fullLines;

        itemEffectManager.applyBlockEffect(clearResult, blockQueue);
        difficultyManager.updateLevel(score, lines, stages);
    }
}

void GameManager::spawnNextBlock()
{
    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
        gameOver = true;
        return;
    }
}

void GameManager::redrawScreen()
{
    Console::drawBoard(board);
    Console::drawGhostBlock(current, board);
    Console::show_block(current);
    Console::drawInfo(
        score,
        lines,
        difficultyManager.getLevel(),
        comboManager.getMultiplier(),
        difficultyManager.getDifficulty()
    );
    Console::drawNextBlocks(blockQueue.preview());
    Console::drawRankings(rankingManager.getTop3());
}
=======
}
>>>>>>> 2b24056ba33a1c51895681e13804e40bc827352f
