#ifndef ACTOR_H
#define ACTOR_H
#include "../Position/Position.h"

class Actor
{
protected:
    Position position;
    int health;

public:
    Actor(Position position, int h);
    Actor();
    ~Actor();
    void moveActor(Position position, char **level);
    int getYPos();
    int getXPos();
    void setPosition(int y, int x);
};
#endif
