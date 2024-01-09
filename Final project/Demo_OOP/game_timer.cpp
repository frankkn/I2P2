#include "game_timer.h"

Game_timer::Game_timer()
{
    gt = 0.0f;
    timer_font = al_load_ttf_font("./font/pirulen.ttf",35,0);
    al_start_timer(game_timer);
    manage_file = new Manage_file();
}

void Game_timer::game_timer_draw()
{
    float highest_score = manage_file -> get_highest_score();
    gt += 1.0f / 60;
    //al_draw_filled_rectangle(0, 0, 250, 125, al_map_rgb(0,0,0));
    al_draw_textf(timer_font, al_map_rgb(255, 255, 255), GAME_WIDTH-410, 20, 0, "Fastest: %.2f", highest_score);
    al_draw_textf(timer_font, al_map_rgb(255, 255, 255), GAME_WIDTH-410, 60, 0, "Time: %.2f", gt);
}

void Game_timer::game_timer_destroy()
{
    al_destroy_timer(game_timer);
    al_destroy_font(timer_font);
}

float Game_timer::get_gt()
{
    return gt;
}
