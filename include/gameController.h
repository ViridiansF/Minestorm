#include "init.h"
#include "update.h"
#include "draw.h"

// gameController.c gère les menus, le lancement et la fin de la partie

void gameLoop(Game* game);
void titleScreen(Game* game);
void gameOver(Game* game);
void gamePaused(Game* game);
void gameRunning(Game* game);
