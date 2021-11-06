#include <ncurses.h>
#include <iostream>
#include "./Player/Player.h"
using namespace std;

int screenSetup();
int mapSetup();
void handleInput(int inputChar, Player &player);

int main()
{
    Player player(0, 0, 100);
    int inputChar;
    screenSetup();
    mapSetup();
    player.moveActor(13, 13);
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
    mvprintw(4, 4, "--------");

    return 0;
}

void handleInput(int inputChar, Player &player)
{
    int currXPos = player.getXPos();
    int currYPos = player.getYPos();

    switch (inputChar)
    {
    case 119:
        player.moveActor(currYPos - 1, currXPos);
        break;
    case 97:
        player.moveActor(currYPos, currXPos - 1);
        break;
    case 115:
        player.moveActor(currYPos + 1, currXPos);
        break;
    case 100:
        player.moveActor(currYPos, currXPos + 1);
        break;
    default:
        break;
    }
}