#include "game.h"

Game::Game() {
}

void Game::init() {
    background = new Background("./image/stars.jpg");
    player = new Player();
    manage_file = new Manage_file();
    game_timer = new Game_timer();

    curLevel = 1;
    levelTimer = al_create_timer(3); // level delay for 3 seconds
    al_start_timer(levelTimer);
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_timer_event_source(levelTimer));

    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font("font/pirulen.ttf", 50, 0);

    BGM = al_load_audio_stream("music/playing_music.mp3", 2, 2048);
    al_set_audio_stream_playmode(BGM, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(BGM, true);
    al_attach_audio_stream_to_mixer(BGM, al_get_default_mixer());

    levelPassMusic = al_load_audio_stream("music/level-pass.mp3", 2, 2048);
    endingMusic = al_load_audio_stream("music/ending_music.mp3", 2, 2048);

    playerGetHitSound = al_load_sample("music/playerGetHitSound.mp3");
    enemyGetHitSound = al_load_sample("music/enemyGetHitSound.mp3");
    playerDeadSound = al_load_sample("music/playerDeadSound.mp3");
    enemyDeadSound = al_load_sample("music/enemyDeadSound.mp3");

    gameOver = false;
    gamePass = false;

    //game_timer_init();
    buff_init();

    enemyImages->loadImages();
    bulletImages->loadImages();

    endingScene = al_load_bitmap("image/ending.jpg");
}

void Game::update() {
    if (gameOver || gamePass) {
        return;
    }

    // Funny effect after killing the last enemy
    for (auto& explosion : explosions) {
        explosion->update();
    }

    player->update();

    if (al_get_timer_started(levelTimer)) {
        ALLEGRO_EVENT event;
        if (al_get_next_event(eventQueue, &event)) {
            al_stop_timer(levelTimer);
            if(enemies.empty()){
                switch (curLevel) {
                    case 1:
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = new Enemy(1);
                            enemies.emplace_back(enemy);

                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = new Enemy(2);
                            enemies.emplace_back(enemy);
                        }
                        break;
                    case 2:
                        for(int i = 0; i < 10; ++i){
                            Enemy* enemy = new Enemy(2);
                            enemies.emplace_back(enemy);
                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = new Enemy(3, i+1);
                            enemies.emplace_back(enemy);
                        }
                        break;
                    case 3:
                        for(int i = 0; i < 3; ++i){
                            Enemy* enemy = new Enemy(3, i+1);
                            enemies.emplace_back(enemy);
                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = new Enemy(4);
                            enemy->radius = 75;
                            enemies.emplace_back(enemy);
                        }
                        break;
                    case 4:
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = new Enemy(4);
                            enemy->radius = 75;
                            enemies.emplace_back(enemy);
                        }
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = new Enemy(5);
                            enemy->radius = 70;
                            enemies.emplace_back(enemy);
                        }
                        break;
                    case 5:
                        for(int i = 0; i < 2; ++i){
                            Enemy* enemy = new Enemy(6);
                            enemy->radius = 70;
                            enemies.emplace_back(enemy);
                        }
                        break;
                    case 6:
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = new Enemy(4);
                            enemy->radius = 75;
                            enemies.emplace_back(enemy);
                        }
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = new Enemy(5);
                            enemy->radius = 70;
                            enemies.emplace_back(enemy);
                        }
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = new Enemy(6);
                            enemy->radius = 70;
                            enemies.emplace_back(enemy);
                        }
                        break;
                    default:
                        break;
                }
                curLevel++;
                if(curLevel == 8){
                    gamePass = true;
                }
                if(curLevel > 1){
                    levelupMusicFlag = true;
                }
            }
        }
    }

    background->update();

    for (auto& enemy : enemies) {
        enemy->update(player->getX(), player->getY());
    }

    // Detect collision between bullets and enemies
    for (auto& bullet : player->getBullets()) {

        float bx = bullet->getX();
        float by = bullet->getY();
        float br = bullet->getRadius();

        for (auto& enemy : enemies) {

            float ex = enemy->getX();
            float ey = enemy->getY();
            float er = enemy->getRadius();

            if (collide(bx, by, br, ex, ey, er)) {
                // Decrease enemy's hp
                enemy->isHit();
                al_play_sample(enemy->isDead() ? enemyDeadSound : enemyGetHitSound,
                               1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &enemyDeadID);
                // kill the bullet (from exist to non-exist)
                bullet->kill();
            }
        }
    }

    // Detect collision between player and enemies
    if(!player->isRecovering()) {
        for(auto& enemy: enemies) {
            auto ex = enemy->getX();
            auto ey = enemy->getY();
            auto er = enemy->getRadius();
            auto px = player->getX();
            auto py = player->getY();
            auto pr = player->getRadius();
            if(!enemy->isRecovering()){
                if(collide(ex, ey, er, px, py, pr)){
                    player->isHit();

                    al_play_sample(player->getHp()==0 && !TEST_MODE ? playerDeadSound:playerGetHitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &playerDeadID);

                    //enemy->isHit();

                    if(player->getHp() == 0 && !TEST_MODE) {
                        gameOver = true;
                    }
                }
            }
        }
    }

    // Detect collision between player and bullets
    if(!player->isRecovering()) {
        for(auto& enemy: enemies) {
            for(auto& bullet : enemy->getBullet()) {
                auto bx = bullet->getX();
                auto by = bullet->getY();
                auto br = bullet->getRadius();
                auto px = player->getX();
                auto py = player->getY();
                auto pr = player->getRadius();
                if(collide(bx, by, br, px, py, pr)){
                    player->isHit();

                    al_play_sample(player->getHp()==0 && !TEST_MODE ? playerDeadSound:playerGetHitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &playerDeadID);

                    bullet->kill();

                    if(player->getHp() == 0 && !TEST_MODE) {
                        gameOver = true;
                    }
                }
            }
        }
    }

    // Detection between players and buffs
    if( buff_show ){
        float bx = buffX;
        float by = buffY;
        float br = buffRadius;
        float px = player->getX();
        float py = player->getY();
        float pr = player->getRadius();
        if(collide(bx, by, br, px, py, pr)){
            buff_update();
            switch( buffType )
            {
            case 0:
                //bulletspeedUp += 10;
                player->addFire();
                break;
            case 1:
                player->speedUp();
                break;
            case 2:
                player->hpAdd();
                break;
            case 3:
                player->hpMinus();
                if(player->getHp() == 0 && !TEST_MODE){
                        gameOver = true;
                }
                break;
            case 4:
                player->bigger();
                break;
            }
        }
    }

    // Remove dead enemies
    for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
        if ((*enemy)->isDead()) {
            float x = (*enemy)->getX();
            float y = (*enemy)->getY();
            float radius = (*enemy)->getRadius();

            explosions.emplace_back(new Explosion(x, y, radius));

            enemies.erase(enemy);
            enemy--;
        }
    }


    // Remove dead explosion
    for (auto explosion = explosions.begin(); explosion != explosions.end(); explosion++) {
        if((*explosion) -> removal()) {
            explosions.erase(explosion);
            explosion--;
        }
    }


    if (enemies.empty()) al_start_timer(levelTimer);
}

void Game::handleInput() {
    if (gameOver || gamePass) {
        // Wait for input
        al_get_keyboard_state(&keyState);
        // Back to the menu
        if (al_key_down(&keyState, ALLEGRO_KEY_Z)) {
            gameOver = false;
            gamePass = false;
            player->destroy();
            menu_init();
            al_set_audio_stream_playing(endingMusic, false);
            window = 1;
            status = 1;
            curLevel = 1;
            levelupMusicFlag = true;

            for (auto& enemy: enemies) {
                enemy->destroy();
                delete enemy;
            }
            enemies.clear();

            al_flush_event_queue(eventQueue);
        }
    }
    player->handleInput();
}

void Game::draw() {
    if (gameOver) {
        buff_show = false;
        al_set_audio_stream_playing(BGM, false);
        // Draw game over text
        al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH / 2, GAME_HEIGHT / 2,
                      ALLEGRO_ALIGN_CENTER, "%s", "Game Over! Press Z to menu.");
        return;
    }

    if (gamePass) {
        al_set_audio_stream_playmode(endingMusic, ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_playing(endingMusic, true);
        al_attach_audio_stream_to_mixer(endingMusic, al_get_default_mixer());
        levelupMusicFlag = false;

        buff_show = false;
        al_set_audio_stream_playing(BGM, false);
        // Draw ending scene
        float score = game_timer->get_gt();
        manage_file->write_file(score);

        al_draw_scaled_bitmap(endingScene, 0, 0, al_get_bitmap_width(endingScene),
                              al_get_bitmap_height(endingScene), 0, 0, GAME_WIDTH, GAME_HEIGHT, 0);
        al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH / 2, GAME_HEIGHT / 2 - 150,
                      ALLEGRO_ALIGN_CENTER, "Your time is: %.2f s", score);
        al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH / 2, GAME_HEIGHT / 2,
                      ALLEGRO_ALIGN_CENTER, "%s", "You win! Frank finally found his carer^_^");
        al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH / 2, GAME_HEIGHT / 2 + 150,
                      ALLEGRO_ALIGN_CENTER, "%s", "Press Z to menu.");

        return;
    }

    background->draw();
    player->draw();

    for (auto& enemy: enemies) {
        enemy->draw();
    }

    for (auto& explosion : explosions) {
        explosion->draw();
    }

    // Draw the level banner
    if (al_get_timer_started(levelTimer)) {
        if (curLevel < 7) {
            al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH / 2, GAME_HEIGHT / 2,
                          ALLEGRO_ALIGN_CENTER, "Level %i", curLevel);
        }
        if (curLevel > 1 && curLevel < 8 && levelupMusicFlag) {
            al_set_audio_stream_playmode(levelPassMusic, ALLEGRO_PLAYMODE_ONCE);
            al_set_audio_stream_playing(levelPassMusic, true);
            al_attach_audio_stream_to_mixer(levelPassMusic, al_get_default_mixer());
            al_set_audio_stream_gain(levelPassMusic, 0.3); // Range: 0.0 (min) to 1.0 (max)
            levelupMusicFlag = false;
        }
    }

    // Draw game timer
    game_timer->game_timer_draw();
}

void Game::destroy() {
    background->destroy();
    player->destroy();
    al_destroy_audio_stream(BGM);
    al_destroy_audio_stream(levelPassMusic);
    al_destroy_audio_stream(endingMusic);

    game_timer->game_timer_destroy();
    buff_destroy();

    for (auto& enemy: enemies) {
        enemy->destroy();
        delete enemy;
    }
    enemies.clear();

    for (auto& explosion : explosions) {
        explosion->destroy();
        delete explosion;
    }
    explosions.clear();

    al_destroy_timer(levelTimer);
    al_destroy_font(font);

    al_destroy_sample(playerGetHitSound);
    al_destroy_sample(playerDeadSound);
    al_destroy_sample(enemyGetHitSound);
    al_destroy_sample(enemyDeadSound);

    enemyImages->destroyImages();
    bulletImages->destroyImages();

    al_destroy_bitmap(endingScene);
}

bool Game::collide(float x1, float y1, float r1, float x2, float y2, float r2) {
    float distX = x1 - x2;
    float distY = y1 - y2;
    float dist = sqrt(distX * distX + distY * distY);

    return dist <= r1 + r2;
}
