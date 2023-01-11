#include "../include/draw.h"



my_Rectangle createRectangle(Vector_2 origin, Vector_2 secondVertex, Vector_2 thirdVertex, Vector_2 fourthVertex)
{
    my_Rectangle rectangle;

    rectangle.vertexTable[0]=origin;
    rectangle.vertexTable[1]=secondVertex;
    rectangle.vertexTable[2]=thirdVertex;
    rectangle.vertexTable[3]=fourthVertex;

    rectangle.center = origin;

    rectangle.directorVector[0]=createVector(rectangle.vertexTable[0],rectangle.vertexTable[1]);
    rectangle.directorVector[1]=createVector(rectangle.vertexTable[1],rectangle.vertexTable[2]);

    rectangle.normalVector[0]=getNormalVector(rectangle.directorVector[0]);
    rectangle.normalVector[1]=getNormalVector(rectangle.directorVector[1]);

    rectangle.radius = sqrt(
        puissance(
            normVector(rectangle.directorVector[0])/2,2)
        +
        puissance(
            normVector(rectangle.directorVector[1])/2,2)
        );
    return rectangle; 
}



my_Rectangle entityToRectangle(Vector_2 position, float width, float height,float angle)
{

    Vector_2 entityVertex[4];

    Vector_2 center = {
        position.x-width,
        position.y-height,
    };


    entityVertex[0] = position;


    entityVertex[1].x=position.x+ width;
    entityVertex[1].y=position.y;
    
    entityVertex[2].x=position.x + width;
    entityVertex[2].y=position.y + height;

    entityVertex[3].x=position.x;
    entityVertex[3].y=position.y+height;


    for(int i=0;i<4;i++)
    {
        entityVertex[i]=rotateVertex(entityVertex[i],center,angle);
    }

    my_Rectangle rectangle = createRectangle(entityVertex[0],entityVertex[1],entityVertex[2],entityVertex[3]);
    return rectangle;
}


void drawPlayerHitBox(Player* player)
{

    Vector_2 vertexTable[4];

    vertexTable[0].x=player->position.x-PLAYER_WIDTH/2;
    vertexTable[0].y=player->position.y-PLAYER_HEIGHT/2;

    vertexTable[1].x=player->position.x+PLAYER_WIDTH/2;
    vertexTable[1].y=player->position.y-PLAYER_HEIGHT/2;

    vertexTable[2].x=player->position.x+PLAYER_WIDTH/2;
    vertexTable[2].y=player->position.y+PLAYER_HEIGHT/2;

    vertexTable[3].x=player->position.x-PLAYER_WIDTH/2;
    vertexTable[3].y=player->position.y+PLAYER_HEIGHT/2;



    for(int i=0;i<4;i++)
    {
        vertexTable[i]=rotateVertex(vertexTable[i],player->position,player->angle+PI/2);
    }

    DrawCircle(vertexTable[0].x,vertexTable[0].y,5,GREEN);
    DrawCircle(vertexTable[1].x,vertexTable[1].y,5,GREEN);
    DrawCircle(vertexTable[2].x,vertexTable[2].y,5,GREEN);
    DrawCircle(vertexTable[3].x,vertexTable[3].y,5,GREEN);


    DrawLine(vertexTable[0].x,vertexTable[0].y,vertexTable[1].x,vertexTable[1].y,RED);
    DrawLine(vertexTable[1].x,vertexTable[1].y,vertexTable[2].x,vertexTable[2].y,RED);
    DrawLine(vertexTable[2].x,vertexTable[2].y,vertexTable[3].x,vertexTable[3].y,RED);
    DrawLine(vertexTable[3].x,vertexTable[3].y,vertexTable[0].x,vertexTable[0].y,RED);

}


void drawEnemyHitBox(Enemy* enemy)
{
    if(enemy->type==TYPE_MINELAYER)
    {
        Vector2 enemyVertexTable[4] ={
            {enemy->position.x-MINELAYER_WIDTH/2,enemy->position.y-MINELAYER_HEIGHT/2},
            {enemy->position.x+MINELAYER_WIDTH/2,enemy->position.y-MINELAYER_HEIGHT/2},
            {enemy->position.x+MINELAYER_WIDTH/2,enemy->position.y+MINELAYER_HEIGHT/2},
            {enemy->position.x-MINELAYER_WIDTH/2,enemy->position.y+MINELAYER_HEIGHT/2},
        };

        for(int i=0;i<4;i++)
        {   
            DrawCircle(enemyVertexTable[i].x,enemyVertexTable[i].y,5,GREEN);   
        }
        DrawLine(enemyVertexTable[0].x,enemyVertexTable[0].y,enemyVertexTable[1].x,enemyVertexTable[1].y,RED);
        DrawLine(enemyVertexTable[1].x,enemyVertexTable[1].y,enemyVertexTable[2].x,enemyVertexTable[2].y,RED);
        DrawLine(enemyVertexTable[2].x,enemyVertexTable[2].y,enemyVertexTable[3].x,enemyVertexTable[3].y,RED);
        DrawLine(enemyVertexTable[3].x,enemyVertexTable[3].y,enemyVertexTable[0].x,enemyVertexTable[0].y,RED);

    }
    else if(enemy->type!=TYPE_FLOATING)
    {
        Vector2 enemyVertexTable[4] ={
            {enemy->position.x-enemy->size/2,enemy->position.y-enemy->size/2},
            {enemy->position.x+enemy->size/2,enemy->position.y-enemy->size/2},
            {enemy->position.x+enemy->size/2,enemy->position.y+enemy->size/2},
            {enemy->position.x-enemy->size/2,enemy->position.y+enemy->size/2},
        };

        for(int i=0;i<4;i++)
        {   
            DrawCircle(enemyVertexTable[i].x,enemyVertexTable[i].y,5,GREEN);   
        }
        DrawLine(enemyVertexTable[0].x,enemyVertexTable[0].y,enemyVertexTable[1].x,enemyVertexTable[1].y,RED);
        DrawLine(enemyVertexTable[1].x,enemyVertexTable[1].y,enemyVertexTable[2].x,enemyVertexTable[2].y,RED);
        DrawLine(enemyVertexTable[2].x,enemyVertexTable[2].y,enemyVertexTable[3].x,enemyVertexTable[3].y,RED);
        DrawLine(enemyVertexTable[3].x,enemyVertexTable[3].y,enemyVertexTable[0].x,enemyVertexTable[0].y,RED);
    }
    else
    {
        
        Vector2 enemyVertexTable[3] = {
            {enemy->position.x,enemy->position.y-enemy->size/2},
            {enemy->position.x-enemy->size/2,enemy->position.y+enemy->size/2},
            {enemy->position.x+enemy->size/2,enemy->position.y+enemy->size/2},
        };


        for(int i=0;i<3;i++)
        {   
            DrawCircle(enemyVertexTable[i].x,enemyVertexTable[i].y,5,GREEN);   
        }
        DrawLine(enemyVertexTable[0].x,enemyVertexTable[0].y,enemyVertexTable[1].x,enemyVertexTable[1].y,RED);
        DrawLine(enemyVertexTable[1].x,enemyVertexTable[1].y,enemyVertexTable[2].x,enemyVertexTable[2].y,RED);
        DrawLine(enemyVertexTable[2].x,enemyVertexTable[2].y,enemyVertexTable[0].x,enemyVertexTable[0].y,RED);
        
    }

}

void drawBulletHitBox(Bullet* bullet)
{}

void drawHitBoxes(Game* game)
{
    if(game->visibleHiboxes)
    {
        Player* player;
        Bullet* bullet;
        Enemy* enemy;
        for(int i=0;i<game->playerCount;i++)
        {
            player=&game->players[i];
            drawPlayerHitBox(player);
            for(int j=0;j<player->bulletCount;j++)
            {            
                bullet= &player->bullets[j];
                drawBulletHitBox(bullet);
            }
        }
        for(int i=0;i<game->enemyCount;i++)
        {
            enemy = &game->enemies[i];
            drawEnemyHitBox(enemy);
        }
        drawEnemyHitBox(&game->minelayer);

    }
}

void drawSpawn(Spawn* spawn)
{

    Rectangle sourceRec = { 0.0f, 0.0f, 57, 57 };
    Rectangle destRec = { spawn->position.x, spawn->position.y, 20, 20 };
    Vector2 origin = { (float)20, (float)20 };


    DrawTexturePro(*spawn->sprite, sourceRec, destRec, origin, (float)0, RED);
   
}

void drawGame(Game* game)
{
    drawBackground(game);

    drawMinelayer(&game->minelayer);

    for(int i = 0; i<game->playerCount;i++)
    {
        if(game->players[i].hp>0)
            drawPlayer(&game->players[i]);

        for(int j = 0; j<game->players[i].bulletCount;j++)
            drawBullet(&game->players[i].bullets[j],game->players[i].playerId);
    }
    for(int i = 0; i<game->enemyCount;i++)
        drawEnemy(&game->enemies[i]);

    for(int i=0;i<game->spawnCount;i++)
        drawSpawn(&game->spawns[i]);

    drawBorders(game);

    drawUI(game);

    drawHitBoxes(game);
}

void drawTitleScreen(Game* game)
{
    drawBackground(game);

    DrawText("Détruisez le Vaisseau Mère alien qui", SCREEN_WIDTH*0.1f+50, SCREEN_HEIGHT*0.2f, 40, YELLOW);

    DrawText("menace la galaxie.", SCREEN_WIDTH/2-150, SCREEN_HEIGHT*0.2f+50, 40, YELLOW);


    DrawText("Il apparait quand vous détruisez ses mines.", 150, SCREEN_HEIGHT*0.2f+150, 35, WHITE);

    DrawText("Bonne chance !", SCREEN_WIDTH/2-150, SCREEN_HEIGHT*0.2f+250, 35, WHITE);


    DrawText("Choisissez votre mode de jeu :", (SCREEN_WIDTH / 2.f)-250, (SCREEN_HEIGHT / 2.f), 30, WHITE);

    DrawText("Appuyez sur \"F\" : Mode 1 joueur", (SCREEN_WIDTH / 2.f)-200, (SCREEN_HEIGHT / 2.f)+100, 20, BLUE);

    DrawText("Appuyez sur \"K\" : Mode 2 joueurs", (SCREEN_WIDTH / 2.f)-200, (SCREEN_HEIGHT / 2.f)+150.f, 20, GREEN);

    DrawText("Appuyez sur \"Esc\" : Quitter", (SCREEN_WIDTH / 2.f)-200, (SCREEN_HEIGHT / 2.f)+200, 20, RED);



    Rectangle sourceRec = { 0.0f, 0.0f, (float)256, (float)256 };
    Rectangle destRec = { 800, 1020, 150, 150 };
    Vector2 origin = { (float)0, (float)0 };
    DrawTexturePro(game->logo, sourceRec, destRec, origin, (float)0, WHITE);


    drawBorders(game);
}

void drawGameOver(Game* game)
{
    drawBackground(game);

    if(game->minelayer.hp<=0)
    {
        DrawText("Félicitation !", (SCREEN_WIDTH / 2.f)-150, (SCREEN_HEIGHT / 2.f)-300.f, 50, WHITE);
        DrawText("Vous avez repoussé la menace alien", (SCREEN_WIDTH / 2.f)-300.f, (SCREEN_HEIGHT / 2.f)-200.f, 35, WHITE);
    }
    else
    {
        DrawText("GAME OVER", (SCREEN_WIDTH / 2.f)-200, (SCREEN_HEIGHT / 2.f)-300.f, 50, WHITE);
        DrawText("Les aliens ont envahi la Terre", (SCREEN_WIDTH / 2.f)-300.f, (SCREEN_HEIGHT / 2.f)-200.f, 35, WHITE);
    }

    DrawText(TextFormat("Player 1 score : %d\n",game->players[0].score),SCREEN_WIDTH/2-175,SCREEN_HEIGHT/2,30,BLUE);


    if(game->playerCount==2)
        DrawText(TextFormat("Player 2 score : %d\n",game->players[1].score),SCREEN_WIDTH/2-175,SCREEN_HEIGHT/2+50,30,GREEN);


    DrawText("Appuyez sur \"Z\" : Retour au menu principal", (SCREEN_WIDTH / 2.f)-300, (SCREEN_HEIGHT / 2.f)+250, 24, WHITE);

    DrawText("Appuyez sur \"Esc\" : Quitter", (SCREEN_WIDTH / 2.f)-200, (SCREEN_HEIGHT / 2.f)+300, 24, WHITE);

    drawBorders(game);
}

void drawPauseMenu(Game* game)
{
    drawBackground(game);

    DrawText("Pause", (SCREEN_WIDTH / 2.f)-100, (SCREEN_HEIGHT / 2.f)-300, 50, WHITE);

    DrawText("Appuyez sur \"ESPACE\" : Reprendre", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)-200, 25, WHITE);

    DrawText("Appuyez sur \"Z\" : Retour au menu principal", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)-150, 25, WHITE);

    DrawText("Appuyez sur \"Esc\" : Quitter", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)-100, 25, WHITE);

    DrawText("Controles Joueur 1 :", (SCREEN_WIDTH / 2.f)-250.f, (SCREEN_HEIGHT / 2.f)-30, 24, BLUE);
    DrawText("Pivoter à droite : G", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f), 20, BLUE);
    DrawText("Pivoter à gauche : D", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)+30, 20, BLUE);
    DrawText("Avancer : R", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)+60, 20, BLUE);
    DrawText("Tirer : F", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)+90, 20, BLUE);
    DrawText("Téléportation : E", (SCREEN_WIDTH / 2.f)-225.f, (SCREEN_HEIGHT / 2.f)+120, 20, BLUE);

    if(game->playerCount==2)
    {
        DrawText("Controles Joueur 2 :", (SCREEN_WIDTH / 2.f)+50, (SCREEN_HEIGHT / 2.f)-30, 24, GREEN);
        DrawText("Pivoter à droite : L", (SCREEN_WIDTH / 2.f)+75, (SCREEN_HEIGHT / 2.f), 20, GREEN);
        DrawText("Pivoter à gauche : J", (SCREEN_WIDTH / 2.f)+75, (SCREEN_HEIGHT / 2.f)+30, 20, GREEN);
        DrawText("Avancer : I", (SCREEN_WIDTH / 2.f)+75, (SCREEN_HEIGHT / 2.f)+60, 20, GREEN);
        DrawText("Tirer : K", (SCREEN_WIDTH / 2.f)+75, (SCREEN_HEIGHT / 2.f)+90, 20, GREEN);
        DrawText("Téléportation : U", (SCREEN_WIDTH / 2.f)+75, (SCREEN_HEIGHT / 2.f)+120, 20, GREEN);       
    }


    drawBorders(game);
}

void drawBackground(Game* game)
{

    int frameWidth = game->background.width/6;
    int frameHeight = game->background.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)SCREEN_WIDTH+100, (float)SCREEN_HEIGHT+100 };

    Rectangle destRec = { 65, SCREEN_HEIGHT-650, SCREEN_WIDTH*2, SCREEN_HEIGHT*2 };

    Vector2 origin = { (float)frameWidth, (float)frameHeight };


    DrawTexturePro(game->background, sourceRec, destRec, origin, (float)0, WHITE);

}


void drawMinelayer(Enemy* minelayer)
{
    int spriteHeight=76;
    int spriteWidth=255;
    Rectangle sourceRec = { 0.0f, 0.0f, spriteWidth, spriteHeight };

    Rectangle destRec = { minelayer->position.x,minelayer->position.y, spriteWidth, 50+spriteHeight };

    Vector2 origin = { (float)MINELAYER_WIDTH/2, (float)MINELAYER_HEIGHT/2 };

    DrawTexturePro(*minelayer->sprite, sourceRec, destRec, origin, (float)180, RED);

}


void drawPlayer(Player* player)
{
    // Dessin du joueur


    int frameWidth = 84;
    int frameHeight = 140;

    Rectangle sourceRec = { 0.0f, 0.0f, frameWidth, frameHeight };
    Rectangle destRec = { player->position.x,player->position.y,frameWidth/2,frameHeight/2 };
    Vector2 origin = { (float)21, (float)35 };



    if(player->invincibilityTimer>0)
        DrawTexturePro(player->sprite, sourceRec, destRec, origin, (float)(player->angle+PI/2)*(180/PI), YELLOW);
    else if(player->playerId==1)
        DrawTexturePro(player->sprite,sourceRec,destRec,origin,player->angle*(180/PI)+90,BLUE);
    else if(player->playerId==2)
        DrawTexturePro(player->sprite, sourceRec, destRec, origin, (float)(player->angle+PI/2)*(180/PI), GREEN);

}

void drawEnemy(Enemy* enemy)
{
    float spriteLargeur, spriteHauteur;

    switch (enemy->type)
    {
        case TYPE_FLOATING:
            spriteLargeur=110.0f;
            spriteHauteur=105.0f;
            break;
        case TYPE_FIREBALL:
            spriteLargeur=100.0f;
            spriteHauteur=105.0f;
            break;
        case TYPE_MAGNETIC:
            spriteLargeur=98.0f;
            spriteHauteur=104.0f;
            break;
        case TYPE_MAGNETIC_FIREBALL:
            spriteLargeur=146.0f;
            spriteHauteur=146.0f;
            break;
        case TYPE_BULLET:
            spriteLargeur=27.0f;
            spriteHauteur=27.0f;
            break;
        case TYPE_SPAWN:
            spriteLargeur=57.0f;
            spriteHauteur=57.0f;
            break;
        default:
            printf("ERROR : Enemy type unknown\n");
            break;
    }

    Rectangle sourceRec = { 0.0f, 0.0f, spriteLargeur, spriteHauteur };
    Rectangle destRec = { enemy->position.x-enemy->size/2, enemy->position.y-enemy->size/2, enemy->size, enemy->size };
    Vector2 origin = { (float)0, (float)0 };


    DrawTexturePro(*enemy->sprite, sourceRec, destRec, origin, (float)0, RED);

}



void drawBullet(Bullet* bullet, int playerId)
{
    if(playerId==1)
        DrawCircle(bullet->position.x, bullet->position.y, 10, BLUE);
    else if(playerId==2)
        DrawCircle(bullet->position.x, bullet->position.y, 10, GREEN);
}

void drawBorders(Game* game)
{

    int frameWidth = game->background.width/6;
    int frameHeight = game->background.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)SCREEN_WIDTH+100, (float)SCREEN_HEIGHT+100 };
    Rectangle destRec = { 65, SCREEN_HEIGHT-650, SCREEN_WIDTH*2, SCREEN_HEIGHT*2 };
    Vector2 origin = { (float)frameWidth, (float)frameHeight };

    DrawTexturePro(game->foreground, sourceRec, destRec, origin, (float)0, WHITE);


}


void drawScore(int score,float posX, float posY)
{
    DrawText(TextFormat("%d\n",score),posX,posY,20,WHITE);
}



void drawUI(Game* game)
{

    //Pause option
    DrawText("ESPACE : PAUSE",280,1245,20,WHITE);
    DrawText("C : HITBOXES",280,1270,20,WHITE);

    // HP player 1
    DrawText("Vies du Joueur 1 :",500,1245,20,WHITE);
    for(int i=0;i<game->players[0].hp;i++)
    {
        DrawText(" o ",685+i*20,1245,20,WHITE);
    }
    
    if(game->playerCount==2)
    {
        // HP player 2
        DrawText("Vies du Joueur 2 :",500,1270,20,WHITE);
        for(int i=0;i<game->players[1].hp;i++)
        {
            DrawText(" o ",685+i*20,1270,20,WHITE);
        }
    }    

    // Score player 1
    DrawText("Score du Joueur 1 :",760,1245,20,WHITE);
    drawScore(game->players[0].score,965,1245);
    
    // Score player 2
    if(game->playerCount==2)
    {
        DrawText("Score du Joueur 2 :",770,1270,20,WHITE);
        drawScore(game->players[1].score,965,1270);
    }    

}


