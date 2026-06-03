#pragma once

class Stage
{
private:
    int speed;
    int stick_rate;
    int clear_line;

public:
    // 기본 수치로 스테이지 초기화
    Stage();
    // 모든 변수를 지정하여 스테이지 초기화
    Stage(int speed, int stick_rate, int clear_line);
    // 속도, 막대 확률만 지정하여 초기화
    Stage(int speed, int stick_rate);
    // 기본 소멸자
    ~Stage();

    // 현재 블록 낙하 속도 반환
    const int getSpeed();
    // 현재 막대 블록 등장 확률 반환
    const int getStick_rate();
    // 레벨업을 위한 클리어 라인 반환
    const int getClear_line();

    // 블록 낙하 속도 설정
    void setSpeed(int speed);
    // 막대 블록 등장 확률 설정
    void setStick_rate(int stick_rate);
    // 레벨업을 위한 클리어 라인 설정
    void setClear_line(int clear_line);
};