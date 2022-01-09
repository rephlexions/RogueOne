#ifndef PLAYER_H
#define PLAYER_H
#include "../Actor/Actor.h"

#include "../Position/Position.h"

class Player : public Actor
{
protected:
public:
    Player(Position pos, int h);
    Player();
    ~Player();
};
#endif
