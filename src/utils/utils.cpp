#include "utils.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void handleInput(int inputChar, Player &player)
{
    int currXPos = player.getXPos();
    int currYPos = player.getYPos();
    int newXPos = 0;
    int newYPos = 0;

    switch (inputChar)
    {
    case 119:
        newXPos = currXPos;
        newYPos = currYPos - 1;
        break;
    case 97:
        newXPos = currXPos - 1;
        newYPos = currYPos;
        break;
    case 115:
        newXPos = currXPos;
        newYPos = currYPos + 1;
        break;
    case 100:
        newXPos = currXPos + 1;
        newYPos = currYPos;
        break;
    default:
        break;
    }

    checkPosition(newYPos, newXPos, player);
}

int checkPosition(int newYPos, int newXPos, Actor &actor)
{
    Position position;
    position.setXPosition(newXPos);
    position.setYPosition(newYPos);
    char c = (mvinch(newYPos, newXPos) & A_CHARTEXT);
    switch (c)
    {
    case 35:
    case 43:
    case 46:
        actor.moveActor(position);
        break;
    default:
        move(actor.getYPos(), actor.getXPos());
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

int mapSetup()
{
    Room rooms[10];
    rooms[0] = createRoom(13, 13, 6, 8);
    rooms[1] = createRoom(40, 2, 6, 8);
    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[0]);
    drawRoom(rooms[1]);
    drawRoom(rooms[2]);
    connectDoors(rooms[0].doors[3], rooms[2].doors[2]);
    connectDoors(rooms[1].doors[2], rooms[0].doors[0]);
    return 0;
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