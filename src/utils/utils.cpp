#include "utils.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

Room rooms[6];

Position handleInput(int inputChar, Player &player)
{
    int currXPos = player.getXPosition();
    int currYPos = player.getYPosition();
    Position newPosition;

    switch (inputChar)
    {
    case 119:
        newPosition.setXPosition(currXPos);
        newPosition.setYPosition(currYPos - 1);
        break;
    case 97:
        newPosition.setXPosition(currXPos - 1);
        newPosition.setYPosition(currYPos);
        break;
    case 115:
        newPosition.setXPosition(currXPos);
        newPosition.setYPosition(currYPos + 1);
        break;
    case 100:
        newPosition.setXPosition(currXPos + 1);
        newPosition.setYPosition(currYPos);
        break;
    default:
        break;
    }

    return newPosition;
}

Monster *getMonsterAt(Position position, Monster *monsters)
{
    for (int i = 0; i < 6; i++)
    {
        if ((position.getYPosition() == monsters[i].getYPosition()) && (position.getXPosition() == monsters[i].getXPosition()))
        {
            return &monsters[i];
        }
    }
}

void killMonster(Monster *monster)
{
    mvprintw(monster->getYPosition(), monster->getXPosition(), ".");
    monster->setAlive(false);
}

int checkPosition(Position newPosition, Level &level)
{
    Position position;
    position.setXPosition(newPosition.getXPosition());
    position.setYPosition(newPosition.getYPosition());

    Player *player = &level.player;
    Monster *monster = getMonsterAt(position, level.monsters);

    char c = (mvinch(newPosition.getYPosition(), newPosition.getXPosition()) & A_CHARTEXT);
    switch (c)
    {
    case 35:
    case 43:
    case 46:
        level.player.moveActor(position, level.getTiles());
        break;
    case 88:
    case 71:
    case 84:
        combat(player, monster, 1);
        break;
    default:
        move(player->getYPosition(), player->getXPosition());
        break;
    }
    return 0;
}

Room *roomsSetup()
{
    for (int i = 0; i < 6; i++)
    {
        rooms[i] = createRoom(i, 4);
        drawRoom(rooms[i]);
    }
    return rooms;
}

char **saveLevelPositions()
{
    char **positions = new char *[25];

    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        positions[y] = new char[100];
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            positions[y][x] = mvinch(y, x);
        }
    }
    return positions;
}

Room createRoom(int grid, int numberOfDoors)
{
    int topX, topY, bottomX, bottomY, leftX, leftY, rightX, rightY;
    Position position(0, 0);
    Room room(position, 0, 0, numberOfDoors);
    Door door(position, false);

    switch (grid)
    {
    case 0:
        room.setXPos(0);
        room.setYPos(0);
        break;
    case 1:
        room.setXPos(33);
        room.setYPos(0);
        break;
    case 2:
        room.setXPos(66);
        room.setYPos(0);
        break;
    case 3:
        room.setXPos(0);
        room.setYPos(14);
        break;
    case 4:
        room.setXPos(33);
        room.setYPos(14);
        break;
    case 5:
        room.setXPos(66);
        room.setYPos(14);
        break;
    default:
        break;
    }

    room.setHeight(rand() % 6 + 4); // max size 9
    room.setWidth(rand() % 14 + 4); // max size 17

    // room offset
    int offsetX = rand() % (30 - room.getWidth() + 1);
    int offsetY = rand() % (10 - room.getHeight() + 1);
    room.setXPos(room.getXPos() + offsetX);
    room.setYPos(room.getYPos() + offsetY);

    for (int i = 0; i < numberOfDoors; i++)
    {
        room.doors[i] = door;
    }

    // top door
    topX = rand() % (room.getWidth() - 2) + room.getXPos() + 1;
    topY = room.getYPos();
    // left door
    leftY = rand() % (room.getHeight() - 2) + room.getYPos() + 1;
    leftX = room.getXPos();
    // bottom door
    bottomX = rand() % (room.getWidth() - 2) + room.getXPos() + 1;
    bottomY = room.getYPos() + room.getHeight() - 1;
    // right door
    rightY = rand() % (room.getHeight() - 2) + room.getYPos() + 1;
    rightX = room.getXPos() + room.getWidth() - 1;
    room.setDoors(topX, topY, leftX, leftY, bottomX, bottomY, rightX, rightY);

    return room;
}

int drawRoom(Room room)
{
    room.drawWalls();
    room.drawDoors();
    return 0;
}

void connectDoors(Level &level)
{
    int randRoom, randDoor, count;
    Room room = level.rooms[0];

    for (int i = 0; i < level.getNumberOfRooms(); i++)
    {
        for (int j = 0; j < level.rooms[i].numberOfDoors; j++)
        {
            if (level.rooms[i].doors[j].isDoorConnected() == true)
            {
                continue;
            }
            count = 0;
            while (count < 10)
            {
                randRoom = rand() % level.getNumberOfRooms();
                randDoor = rand() % level.rooms[randRoom].numberOfDoors;

                if (level.rooms[randRoom].doors[randDoor].isDoorConnected() == 1 || randRoom == 1)
                {
                    count++;
                    continue;
                }
                pathFinding(level.rooms[randRoom].doors[randDoor].getDoorPosition(), level.rooms[i].doors[j].getDoorPosition());
                level.rooms[randRoom].doors[randDoor].setDoorConnected(true);
                level.rooms[i].doors[j].setDoorConnected(true);
                break;
            }
        }
    }
}

int addMonsters(Level &level)
{
    for (int i = 0; i < level.getNumberOfRooms(); i++)
    {
        if ((rand() % 2) == 0)
        {
            level.setMonsters(selectMonster(level.getLevelNumber()), level.getNumberOfMonsters());
            setStartingPosition(level.monsters[level.getNumberOfMonsters()], level.rooms[i]);
            level.setMonsterNumber(++i);
        }
    }
    return 1;
}

Monster selectMonster(int levelNumber)
{
    int monsterType;
    switch (levelNumber)
    {
    case 1:
    case 2:
    case 3:
        monsterType = (rand() % 2) + 1;
        break;
    case 4:
    case 5:
        monsterType = (rand() % 2) + 2;
        break;
    case 6:
        monsterType = 3;
        break;
    default:
        break;
    }

    switch (monsterType)
    {
    case 1:
        // spider
        return createMonster(2, 'X', 1, 1, 1, 1);
    case 2:
        // goblin
        return createMonster(5, 'G', 3, 1, 1, 2);
    case 3:
        // troll
        return createMonster(15, 'T', 5, 1, 1, 1);
    default:
        break;
    }
}

Monster createMonster(int h, char symbol, int attack, int speed, int defence, int pathFinding)
{
    Position pos;
    pos.setXPosition(0);
    pos.setYPosition(0);
    Monster monster(pos, h, symbol, attack, speed, defence, pathFinding);

    return monster;
}

void setStartingPosition(Monster &monster, Room room)
{
    int x = (rand() % room.getWidth() - 2) + room.getXPos() + 1;
    int y = (rand() % room.getHeight() - 2) + room.getYPos() + 1;

    monster.setPosition(y, x);

    mvprintw(monster.getYPosition(), monster.getXPosition(), monster.string);
}

void pathFindingRandom(Monster &monster)
{
    int random = rand() % 5;
    switch (random)
    {
    // step up
    case 0:
        if ((mvinch(monster.getYPosition() - 1, monster.getXPosition()) & A_CHARTEXT) == 46)
        {
            monster.setYPosition(monster.getYPosition() - 1);
        }
        break;
    // step down
    case 1:
        if ((mvinch(monster.getYPosition() + 1, monster.getXPosition()) & A_CHARTEXT) == 46)
        {
            monster.setYPosition(monster.getYPosition() + 1);
        }
        break;
    // step left
    case 2:
        if ((mvinch(monster.getYPosition(), monster.getXPosition() - 1) & A_CHARTEXT) == 46)
        {
            monster.setXPosition(monster.getXPosition() - 1);
        }
        break;
    // step right
    case 3:
        if ((mvinch(monster.getYPosition(), monster.getXPosition() + 1) & A_CHARTEXT) == 46)
        {
            monster.setXPosition(monster.getXPosition() + 1);
        }
        break;
    default:
        break;
    }
}

void pathFindingSeek(Monster &start, Player &destination)
{
    // step left
    if ((abs((start.getXPosition() - 1) - destination.getXPosition()) < abs(start.getXPosition() - destination.getXPosition())) && ((mvinch(start.getYPosition(), start.getXPosition() - 1) & A_CHARTEXT) == 46))
    {
        start.setXPosition(start.getXPosition() - 1);
    }

    // step right
    else if ((abs((start.getXPosition() + 1) - destination.getXPosition()) < abs(start.getXPosition() - destination.getXPosition())) && ((mvinch(start.getYPosition(), start.getXPosition() + 1) & A_CHARTEXT) == 46))
    {
        start.setXPosition(start.getXPosition() + 1);
    }
    // step down
    else if ((abs((start.getYPosition() + 1) - destination.getYPosition()) < abs(start.getYPosition() - destination.getYPosition())) && ((mvinch(start.getYPosition() + 1, start.getXPosition()) & A_CHARTEXT) == 46))
    {
        start.setYPosition(start.getYPosition() + 1);
    }
    // step up
    else if ((abs((start.getYPosition() - 1) - destination.getYPosition()) < abs(start.getYPosition() - destination.getYPosition())) && ((mvinch(start.getYPosition() - 1, start.getXPosition()) & A_CHARTEXT) == 46))
    {
        start.setYPosition(start.getYPosition() - 1);
    }
    else
    {
        // do nothing
    }
}

void moveMonster(Level &level)
{
    for (int i = 0; i < level.getNumberOfMonsters(); i++)
    {
        if (level.monsters[i].isAlive() == 0)
            continue;
        mvprintw(level.monsters[i].getYPosition(), level.monsters[i].getXPosition(), ".");
        if (level.monsters[i].getPathFinding() == 1)
        {
            pathFindingRandom(level.monsters[i]);
        }
        else
        {
            pathFindingSeek(level.monsters[i], level.player);
        }
        mvprintw(level.monsters[i].getYPosition(), level.monsters[i].getXPosition(), level.monsters[i].string);
    }
}

void placePlayer(Room *rooms, Player *player)
{
    player->setXPosition(rooms[3].getXPos() + 1);
    player->setYPosition(rooms[3].getYPos() + 1);
    mvprintw(player->getYPosition(), player->getXPosition(), "@");
    move(player->getYPosition(), player->getXPosition());
}