#include "player.h"

Player::Player() {
    x = GAME_WIDTH / 2;
    y = GAME_HEIGHT - 100;
    radius = 20;
    dx = 0;
    dy = 0;
    speed = 8;
    left = right = up = down = shooting = 0;
    //bullet_count = 0;
    //bullets = (Bullet**)malloc(MAXNO_BULLETS * sizeof(Bullet*));

    hp = 3;

    timer = al_create_timer(1.0 / 5); // 5 bullets per sec
    recTimer = al_create_timer(1.5);  // Immune for 1.5 secs after getting hit
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(recTimer));

    shootSound = al_load_sample("music/dog-barking1.mp3");

    dog = al_load_bitmap("./image/dog.png");
    crydog = al_load_bitmap("./image/dogHit.png");
    hpImage = al_load_bitmap("./image/hp.png");

    width = 80;
    height = 80;

    onFire = 0;
}

void Player::update() {
    if (left) {
        dx = -speed;
    } else if (right) {
        dx = speed;
    } else {
        dx = 0;
    }
    if (up) {
        dy = -speed;
    } else if (down) {
        dy = speed;
    } else {
        dy = 0;
    }

    x += dx;
    y += dy;

    if (x < radius)  // Left boundary
        x = radius;
    if (y < radius)  // Top boundary
        y = radius;
    if (x + radius * 5 > GAME_WIDTH)
        x = GAME_WIDTH - radius * 5;
    if (y + radius * 5 > GAME_HEIGHT)
        y = GAME_HEIGHT - radius * 5;

    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event) && event.timer.source == recTimer) {
        al_stop_timer(recTimer);
    }
    if (shooting) {
        if (!al_get_timer_started(timer)) {
            al_start_timer(timer);
            shootBullet();
        }
        if (event.timer.source == timer) {
            shootBullet();
        }
        if (al_get_next_event(event_queue, &event)) {
            shootBullet();
        }
    } else {  // not firing
        al_stop_timer(timer);
    }

    for (auto& bullet: bullets) {
        bullet->update();
    }

    // Remove bullets
    for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet) {
        if((*bullet)->outOfScreen()) {
            bullets.erase(bullet);
            bullet--;
        }
    }

}

void Player::shootBullet() {
    //bullets.clear();
    if (onFire == 0) {
        Bullet* bullet1 = new Bullet(-90, x, y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullets.emplace_back(bullet1);
    } else if (onFire == 1) {
        Bullet* bullet1 = new Bullet(-80, x, y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullets.emplace_back(bullet1);

        Bullet* bullet2 = new Bullet(-100, x, y, 1);
        bullet2->speed = 20;
        bullet2->dx = cos(bullet2->angle * 3.1415 / 180) * bullet2->speed;
        bullet2->dy = sin(bullet2->angle * 3.1415 / 180) * bullet2->speed;
        bullets.emplace_back( bullet2);
    } else {
        Bullet* bullet1 = new Bullet(-60, x, y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle * 3.1415 / 180) * bullet1->speed;
        bullets.emplace_back(bullet1);

        Bullet* bullet2 = new Bullet(-90, x, y, 1);
        bullet2->speed = 20;
        bullet2->dx = cos(bullet2->angle * 3.1415 / 180) * bullet2->speed;
        bullet2->dy = sin(bullet2->angle * 3.1415 / 180) * bullet2->speed;
        bullets.emplace_back(bullet2);

        Bullet* bullet3 = new Bullet(-120, x, y, 1);
        bullet3->speed = 20;
        bullet3->dx = cos(bullet3->angle * 3.1415 / 180) * bullet3->speed;
        bullet3->dy = sin(bullet3->angle * 3.1415 / 180) * bullet3->speed;
        bullets.emplace_back(bullet3);
    }

    al_play_sample(shootSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &shootID);
}

void Player::handleInput() {
    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);
    left = al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    right = al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    up = al_key_down(&key_state, ALLEGRO_KEY_UP);
    down = al_key_down(&key_state, ALLEGRO_KEY_DOWN);
    shooting = al_key_down(&key_state, ALLEGRO_KEY_SPACE);
}

void Player::draw() {
    if (al_get_timer_started(recTimer)) {
        al_draw_scaled_bitmap(crydog, 0, 0, al_get_bitmap_width(crydog), al_get_bitmap_height(crydog),
                              x, y, width, height, 0);
    } else {
        al_draw_scaled_bitmap(dog, 0, 0, al_get_bitmap_width(dog), al_get_bitmap_height(dog),
                              x, y, width, height, 0);
    }

    for (auto& bullet: bullets) {
        bullet->draw();
    }

    // Draw hp
    for (int i = 0; i < hp; ++i) {
        al_draw_scaled_bitmap(hpImage, 0, 0,
                              al_get_bitmap_width(hpImage), al_get_bitmap_height(hpImage),
                              30, 30 + i * 80,
                              80, 80, 0);
    }
}

void Player::destroy() {
    al_destroy_bitmap(dog);
    al_destroy_bitmap(crydog);
    al_destroy_bitmap(hpImage);

    for (auto& bullet: bullets) {
        delete bullet;
    }

    bullets.clear();

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_timer(recTimer);
    al_destroy_sample(shootSound);
}

float Player::getX() {
    // Return player's x position
    return x;
}
float Player::getY() {
    // Return player's y position
    return y;
}
float Player::getRadius() {
    // Return player's radius
    return radius;
}

/*
// Use bullet_count to avoid using this function
Bullet*** Player::getBullets() {
    // Return a pointer to the array of bullets
    return &bullets;
}
*/

void Player::isHit() {
    --hp;
    al_start_timer(recTimer);
}

int Player::getHp() {
    // Return player's hp
    return hp;
}

int Player::getBulletCount() {
    return bullet_count;
}

bool Player::isRecovering() {
    // Return whether the player is recovering from a hit
    return al_get_timer_started(recTimer);
}

void Player::speedUp() {
    // Increase player's speed
    speed += 3;
}

void Player::hpAdd() {
    // Increase player's hp
    ++hp;
}

void Player::hpMinus() {
    // Decrease player's hp
    --hp;
}

void Player::bigger() {
    // Increase player's size
    width += 20;
    height += 20;
    radius += 5;
}

void Player::addFire() {
    // Activate onFire mode
    onFire += 1;
}
