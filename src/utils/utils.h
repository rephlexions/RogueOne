#ifndef UTILS_H
#define UTILS_H
#include "../Actor/Actor.h"
#include "../Player/Player.h"
#include "../Room/Room.h"
#include "../Monster/Monster.h"
#include "../Level/Level.h"

//screen functions
int screenSetup();
int printGameHub(Level &level);

//player functions
Position handleInput(int inputChar, Player &player);
int checkPosition(Position newPosition, Level &level);
void placePlayer(Room *rooms, Player *player);

//level functions
Room *roomsSetup();
char **saveLevelPositions();

//room functions
Room createRoom(int grid);
int drawRoom(Room room);
int connectDoors(Position start, Position end);

//monster functions
int addMonsters(Level &level);
Monster selectMonster(int levelNumber);
Monster createMonster(int h, char symbol, int attack, int speed, int defence, int pathFinding);
void setStartingPosition(Monster &monster, Room room);
void moveMonster(Level &level);
void pathFindingSeek(Position &start, Position &destination);
void pathFindingRandom(Monster &monster);
void killMonster(Monster *monster);

int combat(Player *player, Monster *monster, int order);

#endif
