
#include "./Room.h"

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

int Room::getXPos()
{
    return this->position.getXPosition();
}
int Room::getYPos()
{
    return this->position.getYPosition();
}
int Room::getHeight()
{
    return this->height;
}
int Room::getWidth()
{
    return this->width;
}