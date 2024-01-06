#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "constants.h"

class Bullet
{
private:
    float x;
    float y;
    float radius;




    bool isExist;

    int owner; // 1:player 2-6: enemy's level

    ALLEGRO_COLOR color;

public:
    Bullet(float angle, float x, float y, int owner);
    ~Bullet();

    float dx;
    float dy;
    float speed;
    float angle;

    void init();
    void update();
    void draw();
    int outOfScreen();

    float getX();
    float getY();
    float getRadius();

    bool checkExist();
    void kill();

    void setColor(ALLEGRO_COLOR _color);
    void setSpeed(int val);

    void loadImages();
    void destroyImages();
};

#endif

