#ifndef ACTOR_H
#define ACTOR_H
#include "../Position/Position.h"

class Actor
{
protected:
    Position position;
    int health;
    int attack;
    bool alive;

public:
    Actor(Position position, int h, int attack);
    Actor();
    ~Actor();
    void moveActor(Position position, char **level);
    int getYPosition();
    int getXPosition();
    void setPosition(int y, int x);
    void setXPosition(int x);
    void setYPosition(int y);
    Position getPosition();
    int getHealth();
    int getAttack();
    void setHealth(int health);
    void setAlive(bool state);
    bool isAlive();
};
#endif
