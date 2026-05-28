#include "GameManager.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

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
    lastDrop(0)
{
    controller.setCurrentBlock(current);
}

void GameManager::run() {
    difficultyManager.select();
    rankingManager.load();

    board.init();
    blockQueue.init(stages, difficultyManager.getLevel());
    current = blockQueue.pop(stages, difficultyManager.getLevel());
    controller.setCurrentBlock(current);

    Console::clear();
    Console::hideCursor();
    redrawScreen();

    if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
        gameOver = true;
    }

    lastDrop = GetTickCount64();

    while (!gameOver) {
        handleInput();
        updateGame();
        redrawScreen();
        Sleep(15);
    }

    rankingManager.saveScore(score);
    redrawScreen();
    Console::drawGameOver();
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
    DWORD now = GetTickCount64();
    int speed = difficultyManager.getCurrentSpeed(score, stages);

    if (now - lastDrop >= static_cast<DWORD>(speed)) {
        bool moved = controller.move(MoveCommand::DOWN);

        if (!moved) {
            fixCurrentBlock(now);
            spawnNextBlock();
        }

        lastDrop = now;
    }
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
