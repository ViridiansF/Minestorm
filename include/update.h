#pragma once

#include "collisions.h"


// Les fonctions d'update.c modifient les valeurs des différentes entités du jeu 

void updateGame();
void updatePlayer();
void updateEnemy();
void updateBullet();
void updateTitleScreen(Game* game);
void updateGameOver(Game* game);
void updatePauseMenu(Game* game);
void spawnEnemy(Game* game);



void removeBullet(Player* player);
void removeEnemy(Game* game);

void collisionCheck(Game* game);
