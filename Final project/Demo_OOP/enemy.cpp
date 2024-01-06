#include "enemy.h"

ALLEGRO_BITMAP *e1, *e2, *e3, *e4, *e5, *e6, *eh1, *eh2, *eh3, *eh4, *eh5, *eh6;
int enemy4angle = 0, enemy5angle = 0;

Enemy::Enemy(int _level)
{
    level = _level;

    radius = 40;
    x = GAME_WIDTH / 2;
    y = 100;
    angle = rand() % 181;
    isOnScreen = false;
    recTimer = al_create_timer(2);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(recTimer));

    switch (level)
    {
        case 1:
            speed = 2;
            hp = 2;
            color = al_map_rgb_f(1, 0, 0);
            break;
        case 2:
            speed = 4;
            hp = 4;
            color = al_map_rgb_f(0, 1, 0);
            break;
        case 4:
            speed = 8;
            hp = 8;
            color = al_map_rgb_f(1, 0, 1);
            break;
        case 5:
            speed = 1;
            hp = 8;
            color = al_map_rgb_f(0, 1, 1);
            break;
        case 6:
            speed = 8;
            hp = 20;
            color = al_map_rgb_f(0, 1, 1);
            break;
    }
    dx = cos(angle) * speed;
    dy = sin(angle) * speed;
}

Enemy::Enemy(int _level, int _speed)
{
    level = _level;

    radius = 40;
    x = GAME_WIDTH / 2;
    y = 100;
    angle = rand() % 181;
    isOnScreen = false;
    recTimer = al_create_timer(2);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(recTimer));

    switch (level)
    {
        case 1:
            speed = 2;
            hp = 2;
            color = al_map_rgb_f(1, 0, 0);
            break;
        case 2:
            speed = 4;
            hp = 4;
            color = al_map_rgb_f(0, 1, 0);
            break;
        case 3:
            // Every frogs must start from different positions
            x = rand() % GAME_WIDTH;
            y = rand() % 100;
            speed = _speed;
            hp = 6;
            color = al_map_rgb_f(0, 0, 1);
            break;
        case 4:
            speed = 8;
            hp = 8;
            color = al_map_rgb_f(1, 0, 1);
            break;
        case 5:
            speed = 8;
            hp = 8;
            color = al_map_rgb_f(0, 1, 1);
            break;
        case 6:
            speed = 8;
            hp = 20;
            color = al_map_rgb_f(0, 1, 1);
            break;
    }
    dx = cos(angle) * speed;
    dy = sin(angle) * speed;
}

void Enemy::update(float playerX, float playerY)
{
    if (level == 3)
    {
        angle = atan2(playerY - y, playerX - x);
        dx = cos(angle) * speed;
        dy = sin(angle) * speed;
    }

    x += dx;
    y += dy;

    if (x > 0 && x < GAME_WIDTH)
        isOnScreen = true;

    // Check boundary
    if (x < radius) // Left boundary
        dx = -dx;
    if (y < radius) // Top boundary
        dy = -dy;
    if (x + radius * 5 > GAME_WIDTH)
        dx = -dx;
    if (y + radius * 5 > GAME_HEIGHT)
        dy = -dy;

    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event))
    {
        al_stop_timer(recTimer);
    }

    if (level == 4)
    {
        int randomProb = rand() % 100;
        if (randomProb <= 1)
        {
            float angle = 30;

            for(int i = 1; i <= 12; ++i) {
                bullets.emplace_back(new Bullet(angle * i * 3.1415 / 180, x, y, level));
            }
        }
    }

    // Very beautiful bullets from level 5 enemy
    if (level == 5)
    {
        float angle = 90 + enemy5angle;
        enemy5angle += 10;
        bullets.emplace_back(new Bullet(angle * 3.14 / 180, x, y, level));

    }

    // Boss will shoot homing missile
    if (level == 6)
    {
        int randomProb = rand() % 100;
        if (randomProb <= 5)
        {
            float angle = atan2(playerY - y, playerX - x);
            Bullet *bullet = new Bullet(angle, x, y, level);
            //bullet->setColor(al_map_rgb_f(1, 0, 0));
            bullets.emplace_back(bullet);
        }
    }

    for (auto& bullet: bullets)
    {
        bullet->update();
    }

    // Remove bullets
    for (auto it = bullets.begin(); it != bullets.end(); )
    {
        if ((*it)->outOfScreen())
        {
            delete *it;          // 刪除 Bullet 物件
            it = bullets.erase(it);  // 刪除 vector 中的元素，erase 會返回下一個有效的迭代器
        }
        else
        {
            ++it;
        }
    }
}

void Enemy::draw()
{
    if (al_get_timer_started(recTimer))
    {
        switch (level)
        {
        case 1:
            al_draw_scaled_bitmap(eh1, 0, 0, al_get_bitmap_width(eh1), al_get_bitmap_height(eh1), x, y, 80, 80, 0);
            break;
        case 2:
            al_draw_scaled_bitmap(eh2, 0, 0, al_get_bitmap_width(eh2), al_get_bitmap_height(eh2), x, y, 80, 80, 0);
            break;
        case 3:
            al_draw_scaled_bitmap(eh3, 0, 0, al_get_bitmap_width(eh3), al_get_bitmap_height(eh3), x, y, 80, 80, 0);
            break;
        case 4:
            al_draw_scaled_bitmap(eh4, 0, 0, al_get_bitmap_width(eh4), al_get_bitmap_height(eh4), x, y, 150, 150, 0);
            break;
        case 5:
            al_draw_scaled_bitmap(eh5, 0, 0, al_get_bitmap_width(eh5), al_get_bitmap_height(eh5), x, y, 200, 200, 0);
            break;
        case 6:
            al_draw_scaled_bitmap(eh6, 0, 0, al_get_bitmap_width(eh6), al_get_bitmap_height(eh6), x, y, 300, 300, 0);
            break;
        }
    }
    else
    {
        switch (level)
        {
        case 1:
            al_draw_scaled_bitmap(e1, 0, 0, al_get_bitmap_width(e1), al_get_bitmap_height(e1), x, y, 80, 80, 0);
            break;
        case 2:
            al_draw_scaled_bitmap(e2, 0, 0, al_get_bitmap_width(e2), al_get_bitmap_height(e2), x, y, 80, 80, 0);
            break;
        case 3:
            al_draw_scaled_bitmap(e3, 0, 0, al_get_bitmap_width(e3), al_get_bitmap_height(e3), x, y, 80, 80, 0);
            break;
        case 4:
            al_draw_scaled_bitmap(e4, 0, 0, al_get_bitmap_width(e4), al_get_bitmap_height(e4), x, y, 150, 150, 0);
            break;
        case 5:
            al_draw_scaled_bitmap(e5, 0, 0, al_get_bitmap_width(e5), al_get_bitmap_height(e5), x, y, 200, 200, 0);
            break;
        case 6:
            al_draw_scaled_bitmap(e6, 0, 0, al_get_bitmap_width(e6), al_get_bitmap_height(e6), x, y, 300, 300, 0);
            break;
        }
    }

    for (auto& bullet: bullets)
    {
        bullet->draw();
    }
}

void Enemy::destroy()
{
    for (auto& bullet: bullets)
    {
        delete bullet;
    }
    bullets.clear();

    al_destroy_timer(recTimer);
    al_destroy_event_queue(event_queue);
}


float Enemy::getX() { return x; }
float Enemy::getY() { return y; }
float Enemy::getRadius() { return radius; }

void Enemy::isHit()
{
    --hp;
    al_start_timer(recTimer);
}

bool Enemy::isDead()
{
    return hp <= 0;
}

bool Enemy::isRecovering()
{
    return al_get_timer_started(recTimer);
}

ALLEGRO_COLOR Enemy::getColor()
{
    return color;
}

void Enemy::loadImages(){
    e1 = al_load_bitmap("image/enemy1.png");
    e2 = al_load_bitmap("image/enemy2.png");
    e3 = al_load_bitmap("image/enemy3.png");
    e4 = al_load_bitmap("image/enemy4.png");
    e5 = al_load_bitmap("image/enemy5.png");
    e6 = al_load_bitmap("image/enemy6.png");
    eh1 = al_load_bitmap("image/enemyHit1.png");
    eh2 = al_load_bitmap("image/enemyHit2.png");
    eh3 = al_load_bitmap("image/enemyHit3.png");
    eh4 = al_load_bitmap("image/enemyHit4.png");
    eh5 = al_load_bitmap("image/enemyHit5.png");
    eh6 = al_load_bitmap("image/enemyHit6.png");
}

void Enemy::destroyImages(){
    al_destroy_bitmap(e1);
    al_destroy_bitmap(e2);
    al_destroy_bitmap(e3);
    al_destroy_bitmap(e4);
    al_destroy_bitmap(e5);
    al_destroy_bitmap(e6);
    al_destroy_bitmap(eh1);
    al_destroy_bitmap(eh2);
    al_destroy_bitmap(eh3);
    al_destroy_bitmap(eh4);
    al_destroy_bitmap(eh5);
    al_destroy_bitmap(eh6);
}
