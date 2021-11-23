#include <ncurses.h>
#include <iostream>
#include <string>
#include <time.h>
#include "./Player/Player.h"
#include "./Room/Room.h"
#include "./Position/Position.h"

using namespace std;

int screenSetup();
int mapSetup();
void handleInput(int inputChar, Player &player);
int checkPosition(int newYPos, int newXPos, Actor &actor);

Room createRoom(int xPos, int yPos, int height, int width);
int drawRoom(Room room);
int connectDoors(Position start, Position end);

int main()
{
    Position position(15, 15);
    Player player(position, 100);
    int inputChar;
    screenSetup();
    mapSetup();
    player.moveActor(position);
    // ASCII 113 -> 'q'
    while ((inputChar = getch()) != 113)
    {
        handleInput(inputChar, player);
    }

    endwin();
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
    connectDoors(rooms[0].doors[3], rooms[2].doors[1]);
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
    Position temp;
    temp.setXPosition(start.getXPosition());
    temp.setYPosition(end.getYPosition());

    while (1)
    {
        // step left
        if ((abs((temp.getXPosition() - 1) - end.getXPosition()) < abs(temp.getXPosition() - end.getXPosition())) && ((mvinch(temp.getYPosition(), temp.getXPosition() - 1) & A_CHARTEXT) == 32))
        {
            mvprintw(temp.getYPosition(), temp.getXPosition() - 1, "#");
            temp.setXPosition(temp.getXPosition() - 1);
        }

        // step right
        else if ((abs((temp.getXPosition() + 1) - end.getXPosition()) < abs(temp.getXPosition() - end.getXPosition())) && ((mvinch(temp.getYPosition(), temp.getXPosition() + 1) & A_CHARTEXT) == 32))
        {
            mvprintw(temp.getYPosition(), temp.getXPosition() + 1, "#");
            temp.setXPosition(temp.getXPosition() + 1);
        }
        // step down
        else if ((abs((temp.getYPosition() + 1) - end.getYPosition()) < abs(temp.getYPosition() - end.getYPosition())) && ((mvinch(temp.getYPosition() + 1, temp.getXPosition()) & A_CHARTEXT) == 32))
        {
            mvprintw(temp.getYPosition() + 1, temp.getXPosition(), "#");
            temp.setYPosition(temp.getYPosition() + 1);
        }
        // step up
        else if ((abs((temp.getYPosition() - 1) - end.getYPosition()) < abs(temp.getYPosition() - end.getYPosition())) && ((mvinch(temp.getYPosition() - 1, temp.getXPosition()) & A_CHARTEXT) == 32))
        {
            mvprintw(temp.getYPosition() - 1, temp.getXPosition(), "#");
            temp.setYPosition(temp.getYPosition() - 1);
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

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