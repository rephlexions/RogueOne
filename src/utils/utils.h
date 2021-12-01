#ifndef UTILS_H
#define UTILS_H
#include "../Actor/Actor.h"
#include "../Player/Player.h"
#include "../Room/Room.h"

void handleInput(int inputChar, Player &player);
int checkPosition(int newYPos, int newXPos, Actor &actor);
int screenSetup();
int mapSetup();
Room createRoom(int xPos, int yPos, int height, int width);
int drawRoom(Room room);
int connectDoors(Position start, Position end);
#endif
