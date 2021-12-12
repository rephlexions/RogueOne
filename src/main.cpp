#include <ncurses.h>
#include <iostream>
#include <string>
#include "./Player/Player.h"
#include "./Room/Room.h"
#include "./Position/Position.h"
#include "./utils/utils.h"

using namespace std;

int main()
{
    Position position(15, 15);
    Position newPosition;
    Player player(position, 100);
    int inputChar;
    char **level;
    screenSetup();
    mapSetup();
    level = saveLevelPositions();
    player.moveActor(position, level);
    // ASCII 113 -> 'q'
    while ((inputChar = getch()) != 113)
    {
        newPosition = handleInput(inputChar, player);
        checkPosition(newPosition, player, level);
    }

    endwin();
    return 0;
}
