#pragma once

class Stage
{
private:
    int speed;
    int stick_rate;
    int clear_line;

public:
    Stage();

    Stage(
        int speed,
        int stick_rate,
        int clear_line
    );

    Stage(
        int speed,
        int stick_rate
    );

    ~Stage();

    const int getSpeed();

    const int getStick_rate();

    const int getClear_line();

    void setSpeed(int speed);

    void setStick_rate(int stick_rate);

    void setClear_line(int clear_line);
};
