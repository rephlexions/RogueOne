#ifndef UTILS_H
#define UTILS_H
#include "../Actor/Actor.h"
#include "../Player/Player.h"
#include "../Room/Room.h"
#include "../Monster/Monster.h"
#include "../Level/Level.h"
#include "../Door/Door.h"

static const int MAX_HEIGHT = 25;
static const int MAX_WIDTH = 100;

// screen functions
int screenSetup();
int printGameHub(Level &level);

// player functions
Position handleInput(int inputChar, Player &player);
int checkPosition(Position newPosition, Level &level);
void placePlayer(Room *rooms, Player *player);
void drawPlayer(Player player);

// level functions
Room *roomsSetup();
char **saveLevelPositions();
void drawLevel(Level level);

// room functions
Room createRoom(int grid, int numberOfDoors);
int drawRoom(Room room);
void connectDoors(Level &level);
void addPositionYX(int **frontier, int frontierCount, int startY, int startX);
int addNeighbors(int **frontier, int ***cameFrom, int frontierCount, int y, int x);
void pathFinding(Position start, Position end);

// monster functions
int addMonsters(Level &level);
Monster selectMonster(int levelNumber);
Monster createMonster(int h, char symbol, int attack, int speed, int defence, int pathFinding);
void setStartingPosition(Monster &monster, Room room);
void moveMonster(Level &level);
void pathFindingSeek(Position &start, Position &destination);
void pathFindingRandom(Monster &monster);
void killMonster(Monster *monster);
void drawMonster(Monster monster);

int combat(Player *player, Monster *monster, int order);

#endif
