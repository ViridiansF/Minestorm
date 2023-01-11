#include "../include/init.h"

void initGame(Game* game)
{

    loadTextures(game);

    loadMusic(game);

    restartGame(game);
}

void restartGame(Game* game)
{
    game->gameTimer=0.0f;
    game->enemyCount=0;
    game->gameStatus=NOT_STARTED;
    game->playerCount=0;
    game->minelayerIsOnScreen=true;
    game->spawnCount=0;
    game->difficulty=0;
    game->visibleHiboxes=false;
    Vector_2 position;

    //  Players initialisation ///////////////////////////////////////////    
    position.x = SCREEN_WIDTH/2-100;
    position.y = SCREEN_HEIGHT/2;
    initPlayer(&game->players[0],position);
    position.x +=200;
    initPlayer(&game->players[1],position);
    //////////////////////////////////////////////////////////////////////

    // Minelayer initialisation /////////////////////////////////////////
    Vector_2 minelayerStartingPosition = {SCREEN_WIDTH/2, 0};
    Vector_2 minelayerStartingDirection = {0,2};

    game->minelayer.type = TYPE_MINELAYER;
    game->minelayer.size = SIZE_LARGE;
    game->minelayer.position = minelayerStartingPosition;
    game->minelayer.direction = minelayerStartingDirection;
    game->minelayer.scoreValue = getScoreValue(&game->minelayer);
    game->minelayer.sprite = &game->enemiesSprites[TYPE_MINELAYER];
    game->minelayer.timer = 0;
    game->difficulty=0;
    game->minelayer.hp = 1200;
    //////////////////////////////////////////////////////////////////////

    
    if(IsMusicStreamPlaying(game->music))
        StopMusicStream(game->music);
    if(IsMusicStreamPlaying(game->titleMusic))
        StopMusicStream(game->titleMusic);
    if(IsMusicStreamPlaying(game->gameOverMusic))
        StopMusicStream(game->gameOverMusic);
    if(IsMusicStreamPlaying(game->victoryMusic))
        StopMusicStream(game->victoryMusic);


}

void loadTextures(Game* game)
{
    game->foreground = LoadTexture("assets/textures/minestorm_foreground.png");
    game->background = LoadTexture("assets/textures/minestorm_background.png");
    game->logo=LoadTexture("assets/textures/logo.png");

    game->enemiesSprites[0] = LoadTexture("assets/textures/ennemiFlottant.png");
    game->enemiesSprites[1] = LoadTexture("assets/textures/ennemiBombardier.png");
    game->enemiesSprites[2] = LoadTexture("assets/textures/ennemiMagnetique.png");
    game->enemiesSprites[3] = LoadTexture("assets/textures/ennemiBombardierMagnetique.png");
    game->enemiesSprites[4] = LoadTexture("assets/textures/ennemiVaisseauMere.png");
    game->enemiesSprites[5] = LoadTexture("assets/textures/balle.png");
    game->enemiesSprites[6] = LoadTexture("assets/textures/ennemiSpawn.png");

    game->players[0].sprite = LoadTexture("assets/textures/spaceShip.png");
    game->players[1].sprite = LoadTexture("assets/textures/spaceShip.png");

    game->players[0].playerId=1;
    game->players[1].playerId=2;

}

void loadMusic(Game* game)
{
    InitAudioDevice();
    game->titleMusic=LoadMusicStream("assets/sound/bgm/titleScreen.wav");
    game->music = LoadMusicStream("assets/sound/bgm/acid.wav");
    game->gameOverMusic=LoadMusicStream("assets/sound/bgm/gameOver.wav");
    game->victoryMusic=LoadMusicStream("assets/sound/bgm/victory.wav");


    SetMusicVolume(game->music,0.7); 
    SetMusicVolume(game->titleMusic,0.7); 
    SetMusicVolume(game->gameOverMusic,0.7); 
    SetMusicVolume(game->victoryMusic,0.7); 


    game->se[0]=LoadSound("assets/sound/se/shipGun.wav");
    game->se[1]=LoadSound("assets/sound/se/playerDeath.wav");
    game->se[2]=LoadSound("assets/sound/se/teleportation.wav");
    game->se[3]=LoadSound("assets/sound/se/criticalHull.wav");
    game->se[4]=LoadSound("assets/sound/se/enemyDestroyed.wav");
    
    for(int i=0;i<2;i++)
    {
        game->players[i].se[0]=&game->se[0];
        game->players[i].se[1]=&game->se[1];
        game->players[i].se[2]=&game->se[2];
        game->players[i].se[3]=&game->se[3];
    }

    SetSoundVolume(game->se[0],0.5);
    SetSoundVolume(game->se[1],0.5);
    SetSoundVolume(game->se[2],0.5);
    SetSoundVolume(game->se[3],0.5);
    SetSoundVolume(game->se[4],0.2);

    
}

void initPlayer(Player* player, Vector_2 position)
{
    player->position=position;
    player->angle = -PI/2;
    player->direction.x = my_cos(player->angle);
    player->direction.y = my_sin(player->angle);
    player->hp=3;
    player->speed=0;
    player->invincibilityTimer=2;
    player->bulletCount=0;
    player->score=0;
}

void unloadGameTextures(Game* game)
{
    UnloadTexture(game->foreground);
    UnloadTexture(game->background);
    UnloadTexture(game->logo);

    for(int i=0;i<NUMBER_ENEMY_SPRITE;i++)
        UnloadTexture(game->enemiesSprites[i]);

    UnloadTexture(game->players[0].sprite);
    UnloadTexture(game->players[1].sprite);
}

void unloadGameMusic(Game* game)
{

    UnloadMusicStream(game->titleMusic);
    UnloadMusicStream(game->music);
    UnloadMusicStream(game->victoryMusic);
    UnloadMusicStream(game->gameOverMusic);

    for(int i=0;i<NUMBER_SOUND_EFFECT;i++)
    {
        UnloadSound(game->se[i]);
    }
}
