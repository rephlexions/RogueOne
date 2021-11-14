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
    Room(Position pos, int h, int w);
    Room();
    ~Room();
    int getXPos();
    int getYPos();
    int getHeight();
    int getWidth();
};
