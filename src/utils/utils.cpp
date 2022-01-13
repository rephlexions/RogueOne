#include "utils.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

Room rooms[3];

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

int checkPosition(Position newPosition, Level &level)
{
    Position position;
    position.setXPosition(newPosition.getXPosition());
    position.setYPosition(newPosition.getYPosition());

    Player player = level.player;
    Monster monster = getMonsterAt(position, level.monsters);

    char c = (mvinch(newPosition.getYPosition(), newPosition.getXPosition()) & A_CHARTEXT);
    switch (c)
    {
    case 35:
    case 43:
    case 46:
        player.moveActor(position, level.getTiles());
        break;
    case 88:
    case 71:
    case 84:

        combat(player, monster, 1);
        break;
    default:
        move(player.getYPosition(), player.getXPosition());
        break;
    }
    return 0;
}

int screenSetup()
{
    srand(time(NULL));
    initscr();
    noecho();
    return 0;
}

Room *roomsSetup()
{
    rooms[0] = createRoom(13, 13, 6, 8);
    rooms[1] = createRoom(40, 2, 6, 8);
    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[0]);
    drawRoom(rooms[1]);
    drawRoom(rooms[2]);
    connectDoors(rooms[0].doors[3], rooms[2].doors[2]);
    connectDoors(rooms[1].doors[2], rooms[0].doors[0]);
    return rooms;
}

char **saveLevelPositions()
{
    char **positions = new char *[25];

    for (int y = 0; y < 25; y++)
    {
        positions[y] = new char[100];
        for (int x = 0; x < 100; x++)
        {
            positions[y][x] = mvinch(y, x);
        }
    }
    return positions;
}

// TODO: refactor
Room createRoom(int xPos, int yPos, int height, int width)
{
    int topX, topY, bottomX, bottomY, leftX, leftY, rightX, rightY;
    Position position;
    position.setXPosition(xPos);
    position.setYPosition(yPos);
    Room room(position, height, width);
    //top door
    topX = rand() % (width - 2) + room.getXPos() + 1;
    topY = room.getYPos();
    //left door
    leftY = rand() % (height - 2) + room.getYPos() + 1;
    leftX = room.getXPos();
    //bottom door
    bottomX = rand() % (width - 2) + room.getXPos() + 1;
    bottomY = room.getYPos() + room.getHeight() - 1;
    //right door
    rightY = rand() % (height - 2) + room.getYPos() + 1;
    rightX = room.getXPos() + width - 1;
    room.setDoors(topX, topY, leftX, leftY, bottomX, bottomY, rightX, rightY);

    return room;
}

int drawRoom(Room room)
{
    room.drawWalls();
    room.drawDoors();
    return 0;
}

int connectDoors(Position start, Position end)
{
    int count = 0;
    Position temp;
    Position prev;
    temp.setXPosition(start.getXPosition());
    temp.setYPosition(start.getYPosition());

    prev = temp;

    while (1)
    {
        // step left
        if ((abs((temp.getXPosition() - 1) - end.getXPosition()) < abs(temp.getXPosition() - end.getXPosition())) && ((mvinch(temp.getYPosition(), temp.getXPosition() - 1) & A_CHARTEXT) == 32))
        {
            prev.setXPosition(temp.getXPosition());
            temp.setXPosition(temp.getXPosition() - 1);
        }

        // step right
        else if ((abs((temp.getXPosition() + 1) - end.getXPosition()) < abs(temp.getXPosition() - end.getXPosition())) && ((mvinch(temp.getYPosition(), temp.getXPosition() + 1) & A_CHARTEXT) == 32))
        {
            prev.setXPosition(temp.getXPosition());
            temp.setXPosition(temp.getXPosition() + 1);
        }
        // step down
        else if ((abs((temp.getYPosition() + 1) - end.getYPosition()) < abs(temp.getYPosition() - end.getYPosition())) && ((mvinch(temp.getYPosition() + 1, temp.getXPosition()) & A_CHARTEXT) == 32))
        {
            prev.setYPosition(temp.getYPosition());
            temp.setYPosition(temp.getYPosition() + 1);
        }
        // step up
        else if ((abs((temp.getYPosition() - 1) - end.getYPosition()) < abs(temp.getYPosition() - end.getYPosition())) && ((mvinch(temp.getYPosition() - 1, temp.getXPosition()) & A_CHARTEXT) == 32))
        {
            prev.setYPosition(temp.getYPosition());
            temp.setYPosition(temp.getYPosition() - 1);
        }
        else
        {
            if (count == 0)
            {
                temp = prev;
                count++;
                continue;
            }
            else
            {
                return 0;
            }
        }
        mvprintw(temp.getYPosition(), temp.getXPosition(), "#");
    }

    return 1;
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
        //goblin
        return createMonster(5, 'G', 3, 1, 1, 2);
    case 3:
        //troll
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
    //step up
    case 0:
        if ((mvinch(monster.getYPosition() - 1, monster.getXPosition()) & A_CHARTEXT) == 46)
        {
            monster.setYPosition(monster.getYPosition() - 1);
        }
        break;
    //step down
    case 1:
        if ((mvinch(monster.getYPosition() + 1, monster.getXPosition()) & A_CHARTEXT) == 46)
        {
            monster.setYPosition(monster.getYPosition() + 1);
        }
        break;
    //step left
    case 2:
        if ((mvinch(monster.getYPosition(), monster.getXPosition() - 1) & A_CHARTEXT) == 46)
        {
            monster.setXPosition(monster.getXPosition() - 1);
        }
        break;
    //step right
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
        //do nothing
    }
}

void moveMonster(Level &level)
{
    for (int i = 0; i < level.getNumberOfMonsters(); i++)
    {
        if (level.monsters[i].getAlive() == 0)
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

Monster getMonsterAt(Position position, Monster *monsters)
{
    for (int i = 0; i < 6; i++)
    {
        if ((position.getYPosition() == monsters[i].getYPosition()) && (position.getXPosition() == monsters[i].getXPosition()))
        {
            return monsters[i];
        }
    }
}

void killMonster(Monster monster)
{
    mvprintw(monster.getYPosition(), monster.getXPosition(), ".");
    monster.setAlive(false);
}
