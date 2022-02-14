#include "./Level.h"
#include "../utils/utils.h"
#include <algorithm>

Level::Level(int levelNumber)
{
    Position position(0, 0);
    Player player(position, 10, 2, 10, 0);

    this->levelNumber = levelNumber;
    this->numberOfRooms = 6;
    this->numberOfMonsters = 0;
    this->rooms = roomsSetup();
    this->tiles = saveLevelPositions();
    this->player = player;

    placePlayer(this->rooms, &this->player);
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