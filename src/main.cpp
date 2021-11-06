#include <ncurses.h>
#include "./Player/Player.h"

int screenSetup();
int mapSetup();

int main()
{
    Player player(13, 13, 100);
    screenSetup();
    mapSetup();
    getch();
    endwin();
    return 0;
}

int screenSetup()
{
    initscr();
    printw("hello world");
    noecho();
    return 0;
}

int mapSetup()
{
    mvprintw(13, 13, "--------");
    mvprintw(13, 13, "|-------|");
    mvprintw(13, 13, "|-------|");
    mvprintw(13, 13, "|-------|");
    mvprintw(13, 13, "--------");

    return 0;
}