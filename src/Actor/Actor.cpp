#include "./Actor.h"
#include <ncurses.h>

Actor::Actor(int x, int y, int h)
{
    xPos = x;
    yPos = y;
    health = h;
}

Actor::~Actor()
{
}

void Actor::moveActor(int y = 13, int x = 13)
{
    mvprintw(this->yPos, this->xPos, ".");
    this->yPos = y;
    this->xPos = x;
    mvprintw(this->yPos, this->xPos, "@");
    move(this->yPos, this->xPos);
}

int Actor::getYPos()
{
    return this->yPos;
}

int Actor::getXPos()
{
    return this->xPos;
}