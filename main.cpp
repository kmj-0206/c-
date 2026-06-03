#include "GameManager.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // 싱글톤 객체를 호출하여 단 하나의 게임 인스턴스 가동
    GameManager::getInstance().run();

    return 0;
}