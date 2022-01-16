#ifndef PLAYER_H
#define PLAYER_H
#include "../Actor/Actor.h"

#include "../Position/Position.h"

class Player : public Actor
{
protected:
    int maxHealth;
    int exp;

public:
    Player(Position pos, int health, int attack, int maxHealth, int exp);
    Player();
    ~Player();

    int getExp();
    void setExp(int exp);
    int getMaxHealth();
};
#endif
