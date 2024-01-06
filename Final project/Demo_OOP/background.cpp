#include "background.h"

Background::Background(const char *filename)
{
    x = 0;
    y = 0;
    backgroundImage = al_load_bitmap(filename);
    if (!backgroundImage)
    {
        printf("Fail to load image.\n");
    }
}

void Background::update()
{
    y += 2;
    if (y >= GAME_HEIGHT)
    {
        y = 0;
    }
}

void Background::draw()
{
    al_draw_scaled_bitmap(backgroundImage, 0, 0,
                          al_get_bitmap_width(backgroundImage),
                          al_get_bitmap_height(backgroundImage),
                          x, y, GAME_WIDTH, GAME_HEIGHT, 0);
    al_draw_scaled_bitmap(backgroundImage, 0, 0,
                          al_get_bitmap_width(backgroundImage),
                          al_get_bitmap_height(backgroundImage),
                          x, y - GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, 0);
}

void Background::destroy()
{
    al_destroy_bitmap(backgroundImage);
}
