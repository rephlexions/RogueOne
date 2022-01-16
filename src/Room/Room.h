#ifndef ROOM_H
#define ROOM_H
#include "../Position/Position.h"

class Room
{
protected:
    Position position;
    int height;
    int width;
    // Monster monster[]
    // Item items[]
public:
    Position doors[4];
    Room(Position pos, int h, int w);
    Room();
    ~Room();
    void setDoors(int topX, int topY, int bottomX, int bottomY, int leftX, int leftY, int rightX, int rightY);
    void drawWalls();
    void drawDoors();
    const Position *getDoors();

    int getXPos();
    int getYPos();
    void setXPos(int x);
    void setYPos(int y);
    int getHeight();
    int getWidth();
    void setHeight(int h);
    void setWidth(int w);
};

#endif