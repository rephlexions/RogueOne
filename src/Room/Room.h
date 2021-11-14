#ifndef ROOM_H
#define ROOM_H
#endif

class Room
{
protected:
    int xPos;
    int yPos;
    int height;
    int width;
    // Monster monster[]
    // Item items[]
public:
    Room(int x, int y, int h, int w);
    Room();
    ~Room();
    int getXPos();
    int getYPos();
    int getHeight();
    int getWidth();
};
