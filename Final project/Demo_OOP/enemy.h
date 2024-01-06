#include "bullet.h"
#include "constants.h"
#include "explosion.h"

class Enemy
{
private:
    int level;
    float x;
    float y;

    float speed;
    float dx;
    float dy;
    float angle;

    int hp;
    bool isOnScreen;

    ALLEGRO_COLOR color;
    ALLEGRO_COLOR recColor;

    std::vector<Bullet*> bullets;

    ALLEGRO_TIMER *recTimer;
    ALLEGRO_EVENT_QUEUE *event_queue;

public:
    Enemy(int);
    Enemy(int, int);

    float radius;

    void init();
    void update(float playerX, float playerY);
    void draw();
    void destroy();

    float getX();
    float getY();
    float getRadius();

    void isHit();
    bool isDead();
    bool isRecovering();

    std::vector<Bullet*> getBullet() { return bullets ;}

    ALLEGRO_COLOR getColor();

    void loadImages();
    void destroyImages();
};
