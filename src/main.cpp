#include <ncurses.h>
#include <iostream>
#include <string>
#include "./Player/Player.h"
#include "./Room/Room.h"
#include "./Position/Position.h"
#include "./Level/Level.h"
#include "./utils/utils.h"

using namespace std;

int main()
{

    Position newPosition;
    int inputChar;
    screenSetup();
    Level level(3);
    addMonsters(level);
    printGameHub(level);
    connectDoors(level);
    level.tiles = saveLevelPositions();
    placePlayer(level.rooms, &level.player);

    while ((inputChar = getch()) != 113)
    {
        newPosition = handleInput(inputChar, level.player);
        checkPosition(newPosition, level);
        moveMonster(level);
        move(level.player.getYPosition(), level.player.getXPosition());
        printGameHub(level);
    }

    endwin();
    return 0;
}
