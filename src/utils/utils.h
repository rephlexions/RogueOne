#ifndef UTILS_H
#define UTILS_H
#include "../Actor/Actor.h"
#include "../Player/Player.h"
#include "../Room/Room.h"

Position handleInput(int inputChar, Player &player);
int checkPosition(Position newPosition, Actor &actor, char **level);
int screenSetup();
Room *roomSetup();
char **saveLevelPositions();
Room createRoom(int xPos, int yPos, int height, int width);
int drawRoom(Room room);
int connectDoors(Position start, Position end);
#endif
