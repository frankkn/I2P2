#include "bullet.h"
#include "constants.h"


class Player {
private:
    float x;
    float y;
    float radius;
    int width;
    int height;
    float dx; // delta_x
    float dy;
    float speed;
    int left;
    int right;
    int up;
    int down;
    bool shooting;
    int onFire;
    int hp;
    int bullet_count;
    std::vector<Bullet*> bullets;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* recTimer;
    ALLEGRO_SAMPLE* shootSound;
    ALLEGRO_SAMPLE_ID shootID;
    ALLEGRO_BITMAP* dog;
    ALLEGRO_BITMAP* crydog;
    ALLEGRO_BITMAP* hpImage;

public:
    Player();

    void update();
    void handleInput();
    void draw();
    void destroy();

    void shootBullet();
    void isHit();
    int getHp();
    int getBulletCount();
    bool isRecovering();

    float getX();
    float getY();
    float getRadius();

    std::vector<Bullet*> getBullets() { return bullets; }

    void speedUp();
    void hpAdd();
    void hpMinus();
    void bigger();
    void addFire();
};
