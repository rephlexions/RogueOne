#ifndef ACTOR_H
#define ACTOR_H
#endif

class Actor
{
protected:
    int xPos;
    int yPos;
    int health;

public:
    Actor(int x, int y, int h);
    ~Actor();
};