#ifndef DOOR_H
#define DOOR_H

#include "../Position/Position.h"

class Door
{
protected:
    Position position;
    bool connected;

public:
    Door(Position position, bool connected);
    Door();
    ~Door();
    void setXPosition(int x);
    void setYPosition(int y);
    int getXPosition();
    int getYPosition();
    Position getDoorPosition();
    bool isDoorConnected();
    void setDoorConnected(bool state);
};
#endif
