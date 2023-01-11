#include "../include/gameController.h"


void gameLoop(Game* game)
{
    if(game->gameStatus==RUNNING)
        gameRunning(game);
    else if(game->gameStatus==PAUSED)
        gamePaused(game);
    else if(game->gameStatus==NOT_STARTED)
        titleScreen(game);
    else if(game->gameStatus==OVER)
        gameOver(game);
}

void titleScreen(Game* game)
{
    PlayMusicStream(game->titleMusic);
    updateTitleScreen(game);
}

void gameRunning(Game* game)
{
    PlayMusicStream(game->music);
    updateGame(game);
}

void gameOver(Game* game)
{
    if(game->minelayer.hp<=0)  
        PlayMusicStream(game->victoryMusic);
    else
        PlayMusicStream(game->gameOverMusic);

    updateGameOver(game);
} 

void gamePaused(Game* game)
{
    updatePauseMenu(game);    
}





