#include "./Actor.h"
#include <ncurses.h>

Actor::Actor(Position pos, int h, int attack)
{
    this->position.setXPosition(pos.getXPosition());
    this->position.setYPosition(pos.getYPosition());
    this->health = h;
    this->attack = attack;
    this->alive = true;
}

Actor::Actor() {}

Actor::~Actor()
{
}

void Actor::moveActor(Position pos, char **level)
{
    // convert a single char to a string of char
    char buffer[8];
    sprintf(buffer, "%c", level[this->position.getYPosition()][this->position.getXPosition()]);

    mvprintw(this->position.getYPosition(), this->position.getXPosition(), buffer);
    this->position.setXPosition(pos.getXPosition());
    this->position.setYPosition(pos.getYPosition());
    mvprintw(this->position.getYPosition(), this->position.getXPosition(), "@");
    move(this->position.getYPosition(), this->position.getXPosition());
}

int Actor::getYPosition()
{
    return this->position.getYPosition();
}

int Actor::getXPosition()
{
    return this->position.getXPosition();
}

void Actor::setPosition(int y, int x)
{
    this->position.setYPosition(y);
    this->position.setXPosition(x);
}

void Actor::setXPosition(int x)
{
    this->position.setXPosition(x);
}
void Actor::setYPosition(int y)
{
    this->position.setYPosition(y);
}

Position Actor::getPosition()
{
    return this->position;
}

int Actor::getHealth()
{
    return this->health;
}

int Actor::getAttack()
{
    return this->attack;
}
void Actor::setHealth(int health)
{
    this->health = health;
}
void Actor::setAlive(bool state)
{
    this->alive = state;
}

bool Actor::isAlive()
{
    return this->alive;
}