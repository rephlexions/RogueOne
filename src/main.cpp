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

    Position position(15, 15);
    Position newPosition;
    Player player(position, 100);
    int inputChar;
    screenSetup();
    Level level(3);
    addMonsters(level);
    player.moveActor(position, level.getTiles());
    // ASCII 113 -> 'q'
    while ((inputChar = getch()) != 113)
    {
        newPosition = handleInput(inputChar, player);
        checkPosition(newPosition, player, level.getTiles());
    }

    endwin();
    return 0;
}
