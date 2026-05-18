#include "GameManager.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

GameManager& GameManager::getInstance() {
   //싱글톤 디자인
    static GameManager instance;
    return instance;
}

GameManager::GameManager()
    : board(),
    stages(5),
    score(0),
    lines(0),
    level(0),
    gameOver(false),
    current(stages[0]->getStick_rate()), // 초기 레벨 0의 데이터 활용
    controller(board),
    lastDrop(0)
{
    // 컨트롤러에 첫 블록 주입
    controller.setCurrentBlock(current);
}

void GameManager::run() {
    // 게임 시작 전 초기 셋팅
    board.init();
    Console::clear();
    Console::hideCursor();
    Console::drawBoard(board);
    Console::drawInfo(score, lines, level);

    // 첫 시작 시 충돌 여부 확인 (게임오버 조건)
    if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
        gameOver = true;
    }

    Console::show_block(current);
    lastDrop = GetTickCount64();

    // 메인 게임 루프 실행
    while (!gameOver) {
        handleInput();
        updateGame();
        Sleep(15);
    }

    // 게임 종료 연출
    Console::drawGameOver();
    Console::gotoxy(0, 25);
}

void GameManager::handleInput() {
    if (_kbhit()) {
        int key = _getch();

        if (key == 27) { // ESC 키 누르면 즉시 종료
            gameOver = true;
            return;
        }

        if (key == 224) { // 화살표 특수키 처리
            key = _getch();
            switch (key) {
            case 75: controller.move(MoveCommand::LEFT);   break;
            case 77: controller.move(MoveCommand::RIGHT);  break;
            case 80: controller.move(MoveCommand::DOWN);   break;
            case 72: controller.move(MoveCommand::ROTATE); break;
            }
        }
        else if (key == ' ') { // 스페이스바 처리
            controller.dropFull();
            lastDrop = 0;
        }
    }
}

void GameManager::updateGame() {
    DWORD now = GetTickCount64();

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
        }

        lastDrop = now;
    }
}