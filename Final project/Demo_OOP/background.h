#include "constants.h"

class Background
{
private:
    int x;
    int y;
    ALLEGRO_BITMAP *backgroundImage;

public:
    Background(const char *filename);

    void update();
    void draw();
    void destroy();
};
