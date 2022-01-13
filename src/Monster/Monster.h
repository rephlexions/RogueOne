#ifndef MONSTER_H
#define MONSTER_H
#include "../Actor/Actor.h"
#include "../Position/Position.h"

class Monster : public Actor
{
protected:
    char symbol;
    int speed;
    int defence;
    int pathFinding;

public:
    char string[2];

    Monster(Position pos, int health, bool alive, char symbol, int attack, int speed, int defence, int pathFinding);
    Monster();
    ~Monster();
    char getSymbol();
    int getPathFinding();
};

#endif
