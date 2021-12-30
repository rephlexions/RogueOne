#include "./Level.h"
#include "../utils/utils.h"
#include <algorithm>

Level::Level(int levelNumber)
{
    this->levelNumber = levelNumber;
    this->numberOfRooms = 3;
    this->numberOfMonsters = 0;
    this->rooms = roomsSetup();
    this->tiles = saveLevelPositions();
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