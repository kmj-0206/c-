#pragma once
#include "Stage.h"
#include <vector>

class StageManager
{
private:
    std::vector<Stage> StageList;// std 혼자 사용
    int count;

public:
    // 기본 5스테이지 생성자
    StageManager();
    // 스테이지 개수를 커스텀하는 생성자
    StageManager(int count);
    // 기본 소멸자
    ~StageManager() = default;

    // 모든 스테이지 내부 수치 일괄 세팅
    void init_Stage();
    // 지정된 레벨의 스테이지 객체 접근 연산자
    Stage* operator[](int level);

    // 총 스테이지 갯수 반환
    int getCount() const { return count; }
};