#include "./Actor.h"
#include <ncurses.h>

Actor::Actor(Position pos, int h)
{
    this->position.setXPosition(pos.getXPosition());
    this->position.setYPosition(pos.getYPosition());
    this->health = h;
}

Actor::~Actor()
{
}

void Actor::moveActor(Position pos, char **level)
{
    char buffer[8];
    sprintf(buffer, "%c", level[this->position.getYPosition()][this->position.getXPosition()]);
    mvprintw(this->position.getYPosition(), this->position.getXPosition(), buffer);
    this->position.setXPosition(pos.getXPosition());
    this->position.setYPosition(pos.getYPosition());
    mvprintw(this->position.getYPosition(), this->position.getXPosition(), "@");
    move(this->position.getYPosition(), this->position.getXPosition());
}

int Actor::getYPos()
{
    return this->position.getYPosition();
}

int Actor::getXPos()
{
    return this->position.getXPosition();
}