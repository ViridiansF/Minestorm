#include "../include/update.h"

bool gameIsOver(Game* game)
{
    // If the minelayer is defeated
    if(game->minelayer.hp<=0)
        return true;

    // If at least one player is alive
    for(int i=0;i<game->playerCount;i++)
    {
        if(game->players[i].hp>0)
            return false;
    }
    return true;
}

void updateTitleScreen(Game* game)
{
    UpdateMusicStream(game->titleMusic);
    drawTitleScreen(game);

    if(IsKeyPressed(KEY_F)) 
    {
        game->gameStatus=RUNNING;
        game->playerCount=1;
    }
    else if(IsKeyPressed(KEY_K))
    {
        game->gameStatus=RUNNING;
        game->playerCount=2;
        game->minelayer.hp=2400;
    }

}

void updateGameOver(Game* game)
{
    if(game->minelayer.hp<=0)
        UpdateMusicStream(game->victoryMusic);
    else
        UpdateMusicStream(game->gameOverMusic);
        
    if(IsKeyPressed(KEY_Z))
        restartGame(game);   

     
    drawGameOver(game);
}

void updatePauseMenu(Game* game)
{
    drawPauseMenu(game);


    if(IsKeyPressed(KEY_SPACE)) 
        game->gameStatus=RUNNING;

    else if(IsKeyPressed(KEY_ESCAPE))  
        game->gameStatus=NOT_STARTED;
    else if(IsKeyPressed(KEY_Z))
        restartGame(game);   

}

void outOfScreen(Vector_2* position)
{
    if(position->y<0) // l'entité passe par le haut de l'écran
    {
        position->y=SCREEN_HEIGHT;
    }
    if(position->y>SCREEN_HEIGHT) // l'entité passe par le bas de l'écran
    {
        //  l'entité repasse de l'autre côté de l'écrank
        position->y=0;
    }
    
    if(position->x<0) // l'entité passe par la gauche de l'écran
    {
        //  l'entité repasse de l'autre côté de l'écran
        position->x=SCREEN_WIDTH;
    }
    if(position->x>SCREEN_WIDTH) // l'entité passe par la droite de l'écran
    {
        //  l'entité repasse de l'autre côté de l'écran
        position->x=0;
    }    
}

void updateFireballs(Game* game,int i)
{
    Enemy* enemy = &game->enemies[i];
        
    if((enemy->type==TYPE_FIREBALL || enemy->type==TYPE_MAGNETIC_FIREBALL)      // Enemy shoot only if it can shoot 
        && game->enemyCount<MAX_ENEMIES && enemy->timer>5.0f)
    {
        enemy->timer=0;
        createNewEnemy(game,TYPE_BULLET,SIZE_BULLET,enemy->position,magneticEffect(game, enemy));
    }
}

void updateMagnetDirection(Game* game,int i)
{
    Enemy* enemy = &game->enemies[i];
    if (enemy->type == TYPE_MAGNETIC || enemy->type == TYPE_MAGNETIC_FIREBALL)
    {
        enemy->direction = magneticEffect(game, enemy);
    }
}

void updateMinelayer(Game* game)
{
    
    Enemy* minelayer = &game->minelayer;
    if(game->minelayerIsOnScreen)
    {
        minelayer->position.y+=minelayer->direction.y;
        drawMinelayer(minelayer);
    
        if(minelayer->position.y>SCREEN_HEIGHT)   
        {
            game->minelayerIsOnScreen=false;
            minelayer->position.y=-20;
        }   

        if(minelayer->timer==1)
        {                 
            for(int i=0;i<game->playerCount;i++)
            {
                game->players[i].invincibilityTimer=2;
            }

            while(minelayer->timer>0 && game->spawnCount<((game->difficulty+STARTING_ENEMY_NUMBER)*7))
            {
                createNewSpawn(game,generateRandomType(),generateRandomPosition());
            }
            
            for(int i=0;i<STARTING_ENEMY_NUMBER+game->difficulty;i++)
            {
                spawnEnemy(game);
            }
            minelayer->timer=0;
        }
    }
}

void spawnEnemy(Game* game)
{
    
    // Create a new enemy
    createNewEnemy(game,generateRandomType(),SIZE_LARGE,game->spawns[0].position,generateRandomDirection());
    
    // Destroy the spawn
    game->spawns[0] = game->spawns[game->spawnCount-1];
    game->spawnCount--;    

}


void spawnEnemyOnDeath(Game* game, Enemy* enemy)
{
    Size size;
    if(enemy->size==SIZE_LARGE)
        size=SIZE_MEDIUM;
    else
        size=SIZE_SMALL;


    // Create a new enemy
    createNewEnemy(game,enemy->type,size,game->spawns[0].position,generateRandomDirection());
    
    // Destroy the spawn
    game->spawns[0] = game->spawns[game->spawnCount-1];
    game->spawnCount--;
    
}

void minelayersAppears(Game* game)
{
    game->difficulty++;
    game->minelayerIsOnScreen=true;
    game->minelayer.timer=1;
}

void updateGame(Game* game)
{

    if(gameIsOver(game))
        game->gameStatus=OVER;
    UpdateMusicStream(game->music);

    if(IsKeyPressed(KEY_SPACE))
        game->gameStatus=PAUSED;
    

    if(IsKeyPressed(KEY_C))
    {
        if(game->visibleHiboxes)
            game->visibleHiboxes=false;
        else
            game->visibleHiboxes=true;
    }
    
    updateMinelayer(game);

    for(int i = 0;i<game->playerCount;i++)
    {
            
        if(game->players[i].hp>0)
        {
            updatePlayer(&game->players[i]);
            outOfScreen(&game->players[i].position);
        }
        else
            game->players[i].position.x=-1000;

        removeBullet(&game->players[i]);
        for(int j = 0;j<game->players[i].bulletCount;j++)
        {
            updateBullet(&game->players[i].bullets[j]);        
            outOfScreen(&game->players[i].bullets[j].position);
        }            


    }
    for(int i = 0; i<game->enemyCount;i++)
    {
        updateFireballs(game,i);
        updateMagnetDirection(game, i);
        updateEnemy(&game->enemies[i]);
        outOfScreen(&game->enemies[i].position);
        removeEnemy(game);
    }
    

    // If there's no spawn the Minelayer appears to add some on screen
    if(game->spawnCount==0)
        minelayersAppears(game);

    drawGame(game);

    collisionCheck(game);
}

void playerControls(Player* player, KeyboardKey goingRight,KeyboardKey goingLeft,KeyboardKey shoot,KeyboardKey accelerate,KeyboardKey teleportation)
{
    if (IsKeyDown(accelerate)) // Le joueur accelère
    {
        if(player->speed<10)
        {
            player->speed+=0.3f;
        }
    }  
    if (IsKeyDown(goingRight)) // Le joueur tourne
    {
        player->angle += PI/45;
        player->direction.x = my_cos(player->angle);
        player->direction.y = my_sin(player->angle);        
    }
    if (IsKeyDown(goingLeft)) // Le joueur tourne
    {
        player->angle -= PI/45;
        player->direction.x = my_cos(player->angle);
        player->direction.y = my_sin(player->angle);
    }
    if (IsKeyPressed(teleportation))
    {
        //Teleportation
        PlaySound(*player->se[PLAYER_TELEPORATION]);

        int posX=GetRandomValue(0,SCREEN_WIDTH), posY=GetRandomValue(0,SCREEN_HEIGHT);
        Vector_2 newPosition = {posX,posY};
        player->position=newPosition;
    }
    if (IsKeyPressed(shoot))
    {        
        if(player->bulletCount<MAX_BULLET)
        {
            PlaySound(*player->se[PLAYER_GUN]);

            Bullet bullet;
            
            // Direction
            bullet.direction.x = player->direction.x;
            bullet.direction.y = player->direction.y;


            // Position
            bullet.position.x=player->position.x;
            bullet.position.y=player->position.y;
    
   
            bullet.hasCollided=false;
            bullet.distanceTravelled=0;
            bullet.radius=5;
            bullet.speed=20;

            player->bullets[player->bulletCount]=bullet;
            player->bulletCount++;
        }
    }

}


void updatePlayer(Player* player)
{

    // Deceleration
    if(player->speed<0.1f && player->speed>-0.1f)
        player->speed=0;
    else if(player->speed>0)
        player->speed-=0.1f;
    else if(player->speed<0)
        player->speed+=0.2f;


    player->position.x += player->direction.x * player->speed;
    player->position.y += player->direction.y * player->speed;


    // Invincibility timer
    if(player->invincibilityTimer>0)
        player->invincibilityTimer-=1.0f/60.0f;


    // Player inputs
    switch (player->playerId)
    {
        case 1:
            playerControls(player,KEY_G,KEY_D,KEY_F,KEY_R,KEY_E);
            break;

        case 2:
            playerControls(player,KEY_L,KEY_J,KEY_K,KEY_I,KEY_U);
            break;

        default:
            printf("ERROR : invalid playerId\n");
            break;
    }

}

void removeEnemy(Game* game)
{
    for(int i=0;i<game->enemyCount;i++)
    {
        Enemy* enemy = &game->enemies[i];

        if(enemy->hp<=0
            || (enemy->type==TYPE_BULLET && enemy->timer>=20.0f))
        {
            if(enemy->size==SIZE_LARGE || enemy->size==SIZE_MEDIUM)
            {
                spawnEnemyOnDeath(game,enemy);
                spawnEnemyOnDeath(game,enemy);
            }
            
            game->enemies[i] = game->enemies[game->enemyCount-1];
            game->enemyCount--;

        }
    }
}

void removeBullet(Player* player)
{
    for(int i=0;i<player->bulletCount;i++)
    {
        Bullet* bullet = &player->bullets[i];

        if(bullet->distanceTravelled>=1000 || bullet->hasCollided)
        {
            player->bullets[i] = player->bullets[player->bulletCount-1];
            player->bulletCount--;
        }
    }
}

void updateBullet(Bullet* bullet)
{
    bullet->position.x += bullet->direction.x * bullet->speed;
    bullet->position.y += bullet->direction.y * bullet->speed;
    bullet->distanceTravelled+=bullet->speed;
}


void updateEnemy(Enemy* enemy)
{
    if(enemy->hp>0)
    {
        enemy->timer+=1.0f/60.0f;
        enemy->position.x+=enemy->direction.x;
        enemy->position.y+=enemy->direction.y;
    }
    else
    {
        enemy->position.x=-1000;
        enemy->position.y=-1000;
        enemy->direction.x=0;
        enemy->direction.y=0;
    }
}

void playerHit(Player* player)
{
    PlaySound(*player->se[PLAYER_DEATH]);
    player->hp--;
    player->invincibilityTimer=2;

    if(player->hp==1)
        PlaySound(*player->se[PLAYER_CRITICALHULL]);
}

void enemyHit(Game* game, int playerIndex, int enemyIndex, int bulletIndex)
{
    PlaySound(game->se[ENEMY_HIT]);
    game->players[playerIndex].score += getScoreValue(&game->enemies[enemyIndex]);
    game->enemies[enemyIndex].hp=0;
    game->players[playerIndex].bullets[bulletIndex].hasCollided=true;
}

void collisionCheck(Game* game)
{
    Enemy* minelayer = &game->minelayer;
    Enemy* enemy;
    Bullet* bullet;
    Player* player;

    for(int i=0;i<game->playerCount;i++)
    {
        player=&game->players[i];

        // Minelayer/Player collisions
        if(player->invincibilityTimer<=0 && collisionEnemyPlayer(minelayer,player))
            playerHit(player);
        

        // Enemy/Player collisions
        for(int j=0;j<game->enemyCount;j++)
        {
            enemy = &game->enemies[j];

            if(player->invincibilityTimer<=0 && collisionEnemyPlayer(enemy,player))
                playerHit(player);


            // Bullet/Enemy collisions
            for(int k=0;k<player->bulletCount;k++)
            {
                bullet=&player->bullets[k];
                if(game->minelayerIsOnScreen)
                    if(collisionBulletEnemy(bullet,minelayer))
                    {
                        PlaySound(game->se[ENEMY_HIT]);
                        minelayer->hp--;
                        bullet->hasCollided=true;              
                    }

                if(collisionBulletEnemy(bullet,enemy))
                    enemyHit(game,i,j,k);
                
            }
        }


        // Bullet/Minelayer collisions
    }
/*
    for(int i=0;i<game->enemyCount;i++)
    {
        enemy = &game->enemies[i];

        for(int j=0;j<game->playerCount;j++)
        {
            player=&game->players[j];

            // Enemy/Player collisions
            if(player->invincibilityTimer<=0 && collisionEnemyPlayer(enemy,player))
            {
                PlaySound(*player->se[PLAYER_DEATH]);
                player->hp--;
                player->invincibilityTimer=2;
            }
            //////

            for(int k=0;k<game->players[j].bulletCount;k++)
            {
                bullet = &player->bullets[k];

                // Bullet/Enemy collisions                    
                if(enemy->type==TYPE_BULLET)
                {
                    if(collisionCircleCircle(enemy->position,enemy->size,bullet->position,bullet->radius))
                    {
                        PlaySound(game->se[ENEMY_HIT]);
                        player->score += getScoreValue(enemy);
                        enemy->hp=0;
                        bullet->hasCollided=true;                            
                    } 
                }                  
                else if(collisionBulletEnemy(bullet,enemy))
                {
                    PlaySound(game->se[ENEMY_HIT]);
                    player->score += getScoreValue(enemy);
                    enemy->hp=0;
                    bullet->hasCollided=true;
                }                         
                //////

                // Minelayer/Bullet collisions
                if(game->minelayerIsOnScreen)
                {
                    if(collisionBulletEnemy(bullet,minelayer))
                    {
                        PlaySound(game->se[ENEMY_HIT]);
                        minelayer->hp--;
                        bullet->hasCollided=true;
                    }
                }
                ///////
            }   
        }
        
    }
    */
}

