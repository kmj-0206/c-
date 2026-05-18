#include "board.h"
#include "BlockControl.h"
#include "Console.h"
#include "StageManager.h"
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Board board;
    board.init();

    StageManager stages(5);
    int score = 0;
    int lines = 0;
    int level = 0;
    bool gameOver = false;

    Console::clear();
    Console::hideCursor();
    Console::drawBoard(board);
    Console::drawInfo(score, lines, level);

    TetrisBlock current(stages[level]->getStick_rate());
    BlockControl controller(board);
    controller.setCurrentBlock(current);

    if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
        gameOver = true;
    }

    Console::show_block(current);

    DWORD lastDrop = GetTickCount();

    while (!gameOver) {
        if (_kbhit()) {
            int key = _getch();

            if (key == 27) break;

            if (key == 224) {
                key = _getch();

                switch (key) {
                case 75:
                    controller.move(MoveCommand::LEFT);
                    break;
                case 77:
                    controller.move(MoveCommand::RIGHT);
                    break;
                case 80:
                    controller.move(MoveCommand::DOWN);
                    break;
                case 72:
                    controller.move(MoveCommand::ROTATE);
                    break;
                }
            }
            else if (key == ' ') {
                controller.dropFull();
                lastDrop = 0;
            }
        }

        DWORD now = GetTickCount();

        if (now - lastDrop >= static_cast<DWORD>(stages[level]->getSpeed())) {
            bool moved = controller.move(MoveCommand::DOWN);

            if (!moved) {
                board.merge(current);
                board.clearFullLines(score, lines, level);

                int newLevel = lines / stages[level]->getClear_line();

                if (newLevel >= stages.getCount()) {
                    newLevel = stages.getCount() - 1;
                }

                level = newLevel;

                Console::drawBoard(board);
                Console::drawInfo(score, lines, level);

                current = TetrisBlock(stages[level]->getStick_rate());
                controller.setCurrentBlock(current);

                if (!controller.canMoveTo({ current.getX(), current.getY(), current.getAngle() })) {
                    gameOver = true;
                    break;
                }

                Console::show_block(current);
            }

            lastDrop = now;
        }

        Sleep(10);
    }

    Console::drawGameOver();
    Console::gotoxy(0, 25);

    return 0;
}