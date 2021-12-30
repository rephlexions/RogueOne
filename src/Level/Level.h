#ifndef LEVEL_H
#define LEVEL_H
#include "../Room/Room.h"
#include "../Monster/Monster.h"
class Level
{
protected:
    int levelNumber;
    char **tiles;
    int numberOfRooms;
    int numberOfMonsters;

public:
    Monster monsters[6];
    Room *rooms;

    Level(int levelNumber);
    ~Level();
    //void setRooms(Room *rooms);
    char **getTiles();
    int getNumberOfRooms();
    int getNumberOfMonsters();
    void setMonsters(Monster monster, int i);
    int getLevelNumber();
    void setMonsterNumber(int x);
};
#endif
