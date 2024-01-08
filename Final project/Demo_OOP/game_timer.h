#ifndef GAME_TIMER_H_INCLUDED
#define GAME_TIMER_H_INCLUDED
#include "constants.h"
#include "manage_file.h"

class Game_timer{
    private:
        ALLEGRO_FONT *timer_font = NULL;
        float gt;
        Manage_file *manage_file;

    public:
        Game_timer();

        void game_timer_init();
        void game_timer_draw();
        void game_timer_destroy();
        float get_gt();
};
#endif
