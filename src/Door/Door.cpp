#include "./Door.h"

Door::Door(Position position, bool connected, bool closed)
{
    this->position = position;
    this->connected = connected;
    this->closed = closed;
}

Door::Door()
{
}

Door::~Door()
{
}

void Door::setXPosition(int x)
{
    this->position.setXPosition(x);
}
void Door::setYPosition(int y)
{
    this->position.setYPosition(y);
}

int Door::getXPosition()
{
    return this->position.getXPosition();
}
int Door::getYPosition()
{
    return this->position.getYPosition();
}

Position Door::getDoorPosition()
{
    return this->position;
}

bool Door::isDoorConnected()
{
    return this->connected;
}

void Door::setDoorConnected(bool state)
{
    this->connected = state;
}

bool Door::isDoorClosed()
{
    return this->closed;
}
bool Door::setDoorClosed(bool state)
{
    this->closed = state;
}
