#ifndef LEVEL_H
#define LEVEL_H
#include "../Room/Room.h"
//#include "../Monster/Monster.h";
class Level
{
private:
    int levelNumber;
    char **tiles;
    int numberOfRooms;
    Room *rooms;
    //Monster **monsters;
    int numberOfMonsters;

public:
    Level(int levelNumber);
    ~Level();
    //Level createLevel(int levelNumber);
    void setRooms(Room *rooms);

    char **getTiles();
};
#endif
