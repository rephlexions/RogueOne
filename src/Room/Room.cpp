
#include "./Room.h"

Room::Room(int x, int y, int h, int w)
{
    this->xPos = x;
    this->yPos = y;
    this->height = h;
    this->width = w;
}
Room::Room() {}

Room::~Room()
{
}

int Room::getXPos()
{
    return this->xPos;
}
int Room::getYPos()
{
    return this->yPos;
}
int Room::getHeight()
{
    return this->height;
}
int Room::getWidth()
{
    return this->width;
}