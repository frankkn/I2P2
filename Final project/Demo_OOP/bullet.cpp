#include "bullet.h"

ALLEGRO_BITMAP *bone, *eb4, *eb5, *eb6;
Bullet::Bullet(float _angle, float _x, float _y, int _owner)
{
    angle = _angle;
    x = _x;
    y = _y;
    owner = _owner;
    isExist = true;
    color = al_map_rgb_f(0.3, 0.7, 0);
    radius = 20;
    speed = 5;
    dx = cos(angle) * speed;
    dy = sin(angle) * speed;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
    x += dx;
    y += dy;
}

void Bullet::draw()
{
    if (owner == 1)
    {
        al_draw_scaled_bitmap(bone, 0, 0, al_get_bitmap_width(bone), al_get_bitmap_height(bone), getX(), getY(), radius, radius, 0);
    }
    else
    {
        switch (owner)
        {
        case 4:
            al_draw_scaled_bitmap(eb4, 0, 0, al_get_bitmap_width(eb4), al_get_bitmap_height(eb4), getX(), getY(), 35, 35, 0);
            break;
        case 5:
            al_draw_scaled_bitmap(eb5, 0, 0, al_get_bitmap_width(eb5), al_get_bitmap_height(eb5), getX(), getY(), 35, 35, 0);
            break;
        case 6:
            al_draw_scaled_bitmap(eb6, 0, 0, al_get_bitmap_width(eb6), al_get_bitmap_height(eb6), getX(), getY(), 35, 35, 0);
            break;
        default:
            break;
        }
    }
}


int Bullet::outOfScreen()
{
    int display_width = al_get_display_width(al_get_current_display());
    int display_height = al_get_display_height(al_get_current_display());

    return (getX() >= display_width ||
            getY() >= display_height ||
            getX() < 0 || getY() < 0 || !isExist);
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
float Bullet::getRadius() { return radius; }
bool Bullet::checkExist() { return isExist; }
void Bullet::kill() { isExist = false; }

void Bullet::setColor(ALLEGRO_COLOR _color) { color = _color; }

void Bullet::setSpeed(int val) { speed = val; }

void Bullet::loadImages()
{
    bone = al_load_bitmap("image/bone.png");
    eb4 = al_load_bitmap("image/bullet4.png");
    eb5 = al_load_bitmap("image/bullet5.png");
    eb6 = al_load_bitmap("image/bullet6.png");
}

void Bullet::destroyImages()
{
    al_destroy_bitmap(bone);
    al_destroy_bitmap(eb4);
    al_destroy_bitmap(eb5);
    al_destroy_bitmap(eb6);
}
