#ifndef POSTION_H
#define POSTION_H
#endif
#pragma once
class Position
{
protected:
    int x;
    int y;

public:
    Position(int x, int y);
    Position();
    ~Position();
    void setXPosition(int x);
    void setYPosition(int y);
    int getXPosition();
    int getYPosition();
};
