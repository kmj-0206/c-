#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <vector>
#include <set>
class TetrisBlock;
class Board;

namespace Console {

    constexpr int ab_x = 5;
    constexpr int ab_y = 1;

    // 지정된 좌표로 커서 이동
    void gotoxy(int x, int y);
    // 콘솔 텍스트 색상 설정
    void SetColor(int color);
    // 콘솔 화면 지우기
    void clear();
    // 콘솔 커서 숨기기
    void hideCursor();

    // 단일 블록 지정 좌표 출력 (마스터 함수)
    void drawBlock(const TetrisBlock& block, int startX, int startY, int mode = 0);

    // 직관적인 래퍼(Wrapper) 함수 복구
    void eraseBlock(const TetrisBlock& block);
    void drawGhostBlock(const TetrisBlock& block, const Board& board);

    // 타이틀 화면 애니메이션 및 텍스트 출력
    void drawTitle();
    // 점수, 남은 라인 수, 레벨 등 정보 출력
    void drawInfo(int score, int lines, int level, int comboMultiplier, int difficulty);
    // 프리뷰 (NEXT 5) 화면 출력
    void drawNextBlocks(const std::vector<TetrisBlock>& nextBlocks);
    // 사이드 미니 랭킹 3위 출력
    void drawSideRankings(const std::vector<int>& ranks);
    // 전체 화면 랭킹 출력
    void drawFullRankings(const std::vector<int>& ranks);

    // 게임 오버 텍스트 출력
    void drawGameOver();
    // 게임 클리어 텍스트 출력
    void drawGameClear();

    // 동적 렌더링 시스템 추적 캐시 초기화
    void clearDynamicCache();
    // 이전 프레임의 동적 블록(현재/고스트) 흔적 지우기
    void eraseDynamic();

    // 보드 전체 정적 화면 출력 (배경, 굳은 블록 등)
    void drawStatic(const Board& board, int level);
    // 실시간 이동/회전 동적 블록 덧그리기
    void drawDynamic(const Board& board, const TetrisBlock& current);
    // 라인 삭제 플래시(깜빡임) 애니메이션 출력
    void drawFlash(const std::set<int>& rows, const Board& board, bool isFlash);

    enum Color {
        BLACK, DARK_BLUE, DARK_GREEN, DARK_SKY_BLUE,
        DARK_RED, DARK_VOILET, DARK_YELLOW, GRAY,
        DARK_GRAY, BLUE, GREEN, SKY_BLUE,
        RED, VOILET, YELLOW, WHITE
    };
}

#endif