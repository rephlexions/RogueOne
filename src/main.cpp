#include <ncurses.h>
#include <iostream>
#include <string>
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

    return 0;
}

Room createRoom(int xPos, int yPos, int height, int width)
{
    Position position;
    position.setXPosition(xPos);
    position.setYPosition(yPos);
    Room room(position, height, width);
    return room;
}

int drawRoom(Room room)
{
    int x;
    int y;
    // draw top and bottom walls
    for (x = room.getXPos(); x < room.getXPos() + room.getWidth(); x++)
    {
        mvprintw(room.getYPos(), x, "-");
        mvprintw(room.getYPos() + room.getHeight() - 1, x, "-");
    }

    //draw fllors and side walls
    for (y = room.getYPos() + 1; y < room.getYPos() + room.getHeight() - 1; y++)
    {
        mvprintw(y, room.getXPos(), "|");
        mvprintw(y, room.getXPos() + room.getWidth() - 1, "|");

        for (x = room.getXPos() + 1; x < room.getXPos() + room.getWidth() - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    return 0;
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
    case 46:
        actor.moveActor(position);
        break;
    default:
        move(actor.getYPos(), actor.getXPos());
        break;
    }
    return 0;
}