#include "explosion.h"

GIF *obj;

double GIF::getTime(double time)
{
    if (start_time == 0)
        start_time = time;
    return time - start_time;
}

void GIF::gifDestroy()
{
    algif_destroy_animation(gif);
}


Explosion::Explosion(float _x, float _y, float _r):x(_x), y(_y), radius(_r), stopExp(false), expTimer(al_get_time()), expTimerDiff(1) {}

void Explosion::update()
{
    radius += 0.5;
    if (al_get_time() - expTimer >= expTimerDiff)
    {
        stopExp = true;
    }
}

void Explosion::draw()
{
    frame = algif_get_bitmap(obj->gif, obj->getTime(al_get_time()));
    al_draw_scaled_bitmap(frame, 0, 0,
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          x, y,
                          radius,
                          radius, 0);

}

bool Explosion::removal()
{
    return stopExp;
}


void Explosion::destroy()
{
    //algif_destroy_animation(obj->gif);
}


void Explosion::loadGIF()
{
    obj = new GIF();
    obj->gif = algif_load_animation("image/explosion1.gif");
}
