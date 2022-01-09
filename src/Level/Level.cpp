#include "./Level.h"
#include "../utils/utils.h"
#include <algorithm>

Level::Level(int levelNumber)
{
    Position position(15, 15);
    Player player(position, 100);

    this->levelNumber = levelNumber;
    this->numberOfRooms = 3;
    this->numberOfMonsters = 0;
    this->rooms = roomsSetup();
    this->tiles = saveLevelPositions();
    this->player = player;

    this->player.moveActor(position, this->getTiles());
}

Level::~Level()
{
}

char **Level::getTiles()
{
    return this->tiles;
}

int Level::getNumberOfRooms()
{
    return this->numberOfRooms;
}

int Level::getNumberOfMonsters()
{
    return this->numberOfMonsters;
}

void Level::setMonsters(Monster monster, int i)
{
    this->monsters[i] = monster;
}

int Level::getLevelNumber()
{
    return this->levelNumber;
}

void Level::setMonsterNumber(int x)
{
    this->numberOfMonsters = x;
}