#ifndef ACTOR_H
#define ACTOR_H
#endif

#include "../Position/Position.h"

class Actor
{
protected:
    Position position;
    int health;

public:
    Actor(Position position, int h);
    ~Actor();
    void moveActor(Position position);
    int getYPos();
    int getXPos();
};