#include <ncurses.h>
#include <iostream>
#include <string>
#include "./Player/Player.h"
#include "./Room/Room.h"
#include "./Position/Position.h"
#include "./Level/Level.h"
#include "./utils/utils.h"
#include "./window/mainMenu.h"

struct Game
{
    Level levels[10];
    int currentLevel;
} Game;

using namespace std;

int main()
{
    struct Game game;
    Level level(0);
    game.currentLevel = 0;
    Position newPosition;
    int inputChar;
    screenSetup();
    // mainMenu(2, choices);
    if (game.currentLevel == 0)
    {
        Level level(1);
        game.levels[game.currentLevel] = level;
        game.currentLevel++;
    }
    level = game.levels[game.currentLevel - 1];

    addMonsters(level);
    printGameHub(level);
    connectDoors(level);
    placePlayer(level.rooms, &level.player);
    level.tiles = saveLevelPositions();

    while ((inputChar = getch()) != 113)
    {
        newPosition = handleInput(inputChar, level.player);
        checkPosition(newPosition, level);
        moveMonster(level);
        // move(level.player.getYPosition(), level.player.getXPosition());
        clear();
        printGameHub(level);
        drawLevel(level);

        if (level.player.getHealth() <= 0)
        {
            game.currentLevel == 0;
            return -1;
        }
    }

    endwin();
    return 0;
}
