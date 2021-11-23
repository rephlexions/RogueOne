#ifndef ROOM_H
#define ROOM_H
#endif

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
    int getXPos();
    int getYPos();
    int getHeight();
    int getWidth();
    void setDoors(int topX, int topY, int bottomX, int bottomY, int leftX, int leftY, int rightX, int rightY);
    void drawWalls();
    void drawDoors();
    const Position *getDoors();
};
