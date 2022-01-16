#include "./Room.h"
#include <ncurses.h>

Room::Room(Position pos, int h, int w)
{
    this->position.setXPosition(pos.getXPosition());
    this->position.setYPosition(pos.getYPosition());
    this->height = h;
    this->width = w;
}
Room::Room() {}

Room::~Room()
{
}

void Room::setDoors(int topX, int topY, int bottomX, int bottomY, int leftX, int leftY, int rightX, int rightY)
{
    this->doors[0].setXPosition(topX);
    this->doors[0].setYPosition(topY);

    this->doors[1].setXPosition(leftX);
    this->doors[1].setYPosition(leftY);

    this->doors[2].setXPosition(bottomX);
    this->doors[2].setYPosition(bottomY);

    this->doors[3].setXPosition(rightX);
    this->doors[3].setYPosition(rightY);
}

void Room::drawWalls()
{
    int x;
    int y;
    // draw top and bottom walls
    for (x = this->getXPos(); x < this->getXPos() + this->getWidth(); x++)
    {
        mvprintw(this->getYPos(), x, "-");
        mvprintw(this->getYPos() + this->getHeight() - 1, x, "-");
    }

    //draw floors and side walls
    for (y = this->getYPos() + 1; y < this->getYPos() + this->getHeight() - 1; y++)
    {
        mvprintw(y, this->getXPos(), "|");
        mvprintw(y, this->getXPos() + this->getWidth() - 1, "|");

        for (x = this->getXPos() + 1; x < this->getXPos() + this->getWidth() - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }
}
void Room::drawDoors()
{
    for (int i = 0; i < 4; i++)
    {
        mvprintw(this->doors[i].getYPosition(), this->doors[i].getXPosition(), "+");
    }
}

int Room::getXPos()
{
    return this->position.getXPosition();
}
int Room::getYPos()
{
    return this->position.getYPosition();
}

void Room::setXPos(int x)
{
    this->position.setXPosition(x);
}
void Room::setYPos(int y)
{
    this->position.setYPosition(y);
}

int Room::getHeight()
{
    return this->height;
}
int Room::getWidth()
{
    return this->width;
}

void Room::setHeight(int h)
{
    this->height = h;
}
void Room::setWidth(int w)
{
    this->width = w;
}

const Position *Room::getDoors()
{
    return doors;
}