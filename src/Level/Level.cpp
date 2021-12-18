#include "./Level.h"
#include "../utils/utils.h"
Level::Level(int levelNumber)
{
    this->levelNumber = levelNumber;
    this->numberOfRooms = 3;
    this->rooms = roomSetup();
    this->tiles = saveLevelPositions();
}

Level::~Level()
{
}

void Level::setRooms(Room *rooms)
{
    this->rooms = rooms;
}

char **Level::getTiles()
{
    return this->tiles;
}

// Level Level::createLevel(int levelNumber)
// {
//     Level newLevel;
//     newLevel.levelNumber = levelNumber;
//     newLevel.numberOfRooms = 3;
//     newLevel.numberOfRooms = roomSetup();

//     return newLevel;
// }