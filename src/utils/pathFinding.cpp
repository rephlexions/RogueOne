#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "./utils.h"
#include <stdlib.h>
#include <ncurses.h>

void addPositionYX(int **frontier, int frontierCount, int startY, int startX)
{
    frontier[frontierCount][0] = startY;
    frontier[frontierCount][1] = startX;
}

bool checkWalls(int y, int x)
{
    char temp = (mvinch(y, x) & A_CHARTEXT);
    if (temp == 46 || temp == 124 || temp == 45)
    {
        return false;
    }
    return true;
}

int addNeighbors(int **frontier, int ***cameFrom, int frontierCount, int y, int x)
{
    // north
    if (y > 0 && cameFrom[y - 1][x][0] < 0 && checkWalls(y - 1, x))
    {
        addPositionYX(frontier, frontierCount, y - 1, x);
        frontierCount++;
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
    }

    // south
    if (y < (MAX_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && checkWalls(y + 1, x))
    {
        addPositionYX(frontier, frontierCount, y + 1, x);
        frontierCount++;
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
    }

    // east
    if (x < (MAX_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && checkWalls(y, x + 1))
    {
        addPositionYX(frontier, frontierCount, y, x + 1);
        frontierCount++;
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
    }

    // west
    if (x > 0 && cameFrom[y][x - 1][0] < 0 && checkWalls(y, x - 1))
    {
        addPositionYX(frontier, frontierCount, y, x - 1);
        frontierCount++;
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
    }

    return frontierCount;
}

void pathFinding(Position start, Position end)
{
    int x, y, tempY;
    int frontierIndex = 0;
    int frontierCount = 0;
    int **frontier = (int **)malloc(sizeof(int *) * MAX_HEIGHT * MAX_WIDTH);
    int ***cameFrom = (int ***)malloc(sizeof(int **) * MAX_HEIGHT);

    for (int i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++)
    {
        frontier[i] = (int *)malloc(sizeof(int) * 2);
    }

    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        cameFrom[i] = (int **)malloc(sizeof(int *) * MAX_WIDTH);
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            cameFrom[i][j] = (int *)malloc(sizeof(int) * 2);
            cameFrom[i][j][0] = -1;
            cameFrom[i][j][1] = -1;
        }
    }
    cameFrom[start.getYPosition()][start.getXPosition()][0] = -9;
    cameFrom[start.getYPosition()][start.getXPosition()][1] = -9;

    addPositionYX(frontier, frontierCount, start.getYPosition(), start.getXPosition());
    frontierCount++;

    while (frontierIndex < frontierCount)
    {
        y = frontier[frontierIndex][0];
        x = frontier[frontierIndex][1];
        frontierIndex++;

        if (y == end.getYPosition() && x == end.getXPosition())
        {
            break;
        }
        frontierCount = addNeighbors(frontier, cameFrom, frontierCount, y, x);
    }

    y = end.getYPosition();
    x = end.getXPosition();

    while (y != start.getYPosition() || x != start.getXPosition())
    {
        tempY = y;
        y = cameFrom[y][x][0];
        x = cameFrom[tempY][x][1];
        mvprintw(y, x, "+");
    }
}

#endif
