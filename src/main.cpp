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
