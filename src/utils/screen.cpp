#ifndef SCREEN_H
#define SCREEN_H

#include "./utils.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int screenSetup()
{
    srand(time(NULL));
    initscr();
    noecho();
    return 0;
}

int printGameHub(Level &level)
{
    Player *player = &level.player;
    mvprintw(25, 0, "    Level: %d", level.getLevelNumber());
    //printw("Gold: %d", player->getGold());
    printw("    HP: %d(%d)", player->getHealth(), player->getMaxHealth());
    printw("    Attack: %d", player->getAttack());
    printw("    Exp: %d", player->getExp());
    printw("      ");
}

#endif