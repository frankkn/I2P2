#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "constants.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "menu.h"
#include "game_timer.h"
#include "buff.h"
#include "bullet.h"
#include "manage_file.h"

class Game {
    private:
        Background* background;
        Player *player;

        Enemy *enemyImages;
        Bullet *bulletImages;

        Manage_file *manage_file;
        Game_timer *game_timer;

        std::vector<Enemy *> enemies;
        std::vector<Explosion *> explosions;

        bool gameOver;
        bool gamePass;

        int curLevel;
        ALLEGRO_TIMER* levelTimer;
        ALLEGRO_EVENT_QUEUE* eventQueue;

        ALLEGRO_FONT* font;
        ALLEGRO_AUDIO_STREAM* BGM;
        bool levelupMusicFlag;
        ALLEGRO_AUDIO_STREAM* levelPassMusic;
        ALLEGRO_AUDIO_STREAM* endingMusic;

        ALLEGRO_SAMPLE* playerGetHitSound;
        ALLEGRO_SAMPLE* enemyGetHitSound;

        ALLEGRO_SAMPLE_ID playerDeadID;

        ALLEGRO_SAMPLE* playerDeadSound;
        ALLEGRO_SAMPLE* enemyDeadSound;

        ALLEGRO_SAMPLE_ID enemyDeadID;

        ALLEGRO_KEYBOARD_STATE keyState;

        ALLEGRO_BITMAP* endingScene;

        bool collide(float x1, float y1, float w1, float h1, float x2, float y2);

        void updateGame();
        void drawGame();
        void handleInputGame();
        void destroyGame();

    public:
        Game();

        void init();
        void update();
        void handleInput();
        void draw();
        void destroy();
};

#endif
