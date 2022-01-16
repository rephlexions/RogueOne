#include "./Monster.h"
#include <stdio.h>

Monster::Monster(Position pos, int health, char symbol, int attack, int speed, int defence, int pathFinding) : Actor(pos, health, attack)
{
    this->symbol = symbol;
    this->speed = speed;
    this->defence = defence;
    this->pathFinding = pathFinding;

    sprintf(this->string, "%c", symbol);
}

Monster::Monster()
{
}

Monster::~Monster() {}

char Monster::getSymbol()
{
    return this->symbol;
}

int Monster::getPathFinding()
{
    return this->pathFinding;
}