#include <ncurses.h>
#include <iostream>
#include <string>

#include "./Player/Player.h"
using namespace std;

int screenSetup();
int mapSetup();
void handleInput(int inputChar, Player &player);
int checkPosition(int newYPos, int newXPos, Actor &actor);

int main()
{
    Player player(0, 0, 100);
    int inputChar;
    screenSetup();
    mapSetup();
    player.moveActor(15, 15);
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
    mvprintw(13, 13, "---------");
    mvprintw(14, 13, "|.......|");
    mvprintw(15, 13, "|.......|");
    mvprintw(16, 13, "|.......|");
    mvprintw(17, 13, "|.......|");
    mvprintw(18, 13, "---------");

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|.......|");
    mvprintw(4, 40, "|.......|");
    mvprintw(5, 40, "|.......|");
    mvprintw(6, 40, "|.......|");
    mvprintw(7, 40, "---------");

    mvprintw(10, 40, "---------");
    mvprintw(11, 40, "|.......|");
    mvprintw(12, 40, "|.......|");
    mvprintw(13, 40, "|.......|");
    mvprintw(14, 40, "|.......|");
    mvprintw(15, 40, "---------");

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
    char c = (mvinch(newYPos, newXPos) & A_CHARTEXT);
    switch (c)
    {
    case 46:
        actor.moveActor(newYPos, newXPos);
        break;
    default:
        move(actor.getYPos(), actor.getXPos());
        break;
    }
}