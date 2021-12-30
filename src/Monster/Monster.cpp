#include "./Monster.h"

Monster::Monster(Position pos, int h, char symbol, int attack, int speed, int defence, int pathFinding) : Actor(pos, h)
{
    this->symbol = symbol;
    this->attack = attack;
    this->speed = speed;
    this->defence = defence;
    //TODO: implement random path finding
    this->pathFinding = 0;
}

Monster::Monster()
{
}

Monster::~Monster() {}

char Monster::getSymbol()
{
    return this->symbol;
}