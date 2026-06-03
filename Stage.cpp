#include "Stage.h"

Stage::Stage(
    int speed,
    int stick_rate,
    int clear_line)
    : speed(speed),
    stick_rate(stick_rate),
    clear_line(clear_line)
{
}

Stage::Stage()
    : Stage(300, 20, 20)
{
}

Stage::~Stage()
{
}

Stage::Stage(
    int speed,
    int stick_rate)
    : Stage(speed, stick_rate, 20)
{
}

const int Stage::getSpeed()
{
    return speed;
}

const int Stage::getStick_rate()
{
    return stick_rate;
}

const int Stage::getClear_line()
{
    return clear_line;
}

void Stage::setSpeed(int speed)
{
    this->speed = speed;
}

void Stage::setStick_rate(int stick_rate)
{
    this->stick_rate = stick_rate;
}

void Stage::setClear_line(int clear_line)
{
    this->clear_line = clear_line;
}