#ifndef CONSTANTS__H__INCLUDED
#define CONSTANTS__H__INCLUDED

#include "constants.h"

class GIF
{
    private:
        double start_time;

    public:
        GIF() { start_time = 0; }

        ALGIF_ANIMATION *gif;
        double getTime(double);
        void gifDestroy();
};

class Explosion
{
    private:
        float x;
        float y;
        float radius;
        float expTimer;
        float expTimerDiff;
        bool stopExp;
        ALLEGRO_BITMAP *frame;

    public:
        Explosion(float, float, float);

        void update();
        void draw();
        void destroy();
        bool removal();
        void loadGIF();
};

#endif
