#include "./Door.h"

Door::Door(Position position, bool connected)
{
    this->position = position;
    this->connected = connected;
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

bool Door::isDoorConnected()
{
    return this->connected;
}

Position Door::getDoorPosition()
{
    return this->position;
}

void Door::setDoorConnected(bool state)
{
    this->connected = state;
}
