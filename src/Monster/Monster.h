#ifndef MONSTER_H
#define MONSTER_H
#include "../Actor/Actor.h"
#include "../Position/Position.h"

class Monster : public Actor
{
protected:
    char symbol;
    int attack;
    int speed;
    int defence;
    int pathFinding;

public:
    Monster(Position pos, int h, char symbol, int attack, int speed, int defence, int pathFinding);
    Monster();
    ~Monster();
    char getSymbol();
};

#endif
