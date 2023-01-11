#include "../include/tools.h"

Vector_2 magneticEffect(Game* game, Enemy* enemy)
{
    Vector_2 closestPlayerDirection;
    if (game->playerCount== 2)
    {
        Vector_2 player1Direction = createVector(enemy->position,game->players[0].position);
        Vector_2 player2Direction = createVector(enemy->position,game->players[1].position);
        closestPlayerDirection = getSmallestVector(player1Direction, player2Direction);
    }
    else
    {
        closestPlayerDirection = createVector(enemy->position,game->players[0].position);
    }

    Vector_2 magneticDirection = {closestPlayerDirection.x / normVector(closestPlayerDirection), closestPlayerDirection.y / normVector(closestPlayerDirection)};
    if (enemy->type == TYPE_BULLET)
    {
        magneticDirection.x *= 10;
        magneticDirection.y *= 10;
    }

    return magneticDirection;
}

Vector_2 generateRandomDirection()
{
    float dirX,dirY;  
    dirX = GetRandomValue(-10,10);
    dirY = GetRandomValue(-10,10);
    dirX/=10;
    dirY/=10;

    Vector_2 randomDirection = {dirX,dirY}; 
    return randomDirection;
}

void createNewSpawn(Game* game, Type type, Vector_2 position)
{
    Spawn* spawn = &game->spawns[game->spawnCount];

    spawn->type=type;
    spawn->position=position;
    spawn->sprite=&game->enemiesSprites[TYPE_SPAWN];

    game->spawnCount++;
}

void createNewEnemy(Game* game, Type type, Size size, Vector_2 position, Vector_2 direction)
{
    Enemy* enemy = &game->enemies[game->enemyCount];

    enemy->type=type;
    enemy->size=size;
    enemy->position=position;
    enemy->direction=direction;

    enemy->hp=1;
    enemy->scoreValue=getScoreValue(enemy);
    enemy->sprite=&game->enemiesSprites[type];
    enemy->timer=0;

    if(size!=SIZE_LARGE)
        enemy->timer=5.0f;

    game->enemyCount++;
}   

Vector_2 generateRandomPosition()
{
    int posX,posY;

    posX = GetRandomValue(200,SCREEN_WIDTH-200);
    posY = GetRandomValue(200,SCREEN_HEIGHT-200);  

    Vector_2 randomPosition = {posX,posY}; 
    return randomPosition;
}

Type generateRandomType()
{
    switch (GetRandomValue(0,3))
    {
        case 0:
            return TYPE_FLOATING;
        case 1:
            return TYPE_FIREBALL;
        case 2:
            return TYPE_MAGNETIC;
        default:
            return TYPE_MAGNETIC_FIREBALL;
    }  
}

int getScoreValue(Enemy* enemy)
{
    int scoreValue = 0;

    switch (enemy->type)
    {
    case TYPE_FLOATING:
        scoreValue+=100;
        break;

    case TYPE_MAGNETIC:
        scoreValue+=500;
        break;

    case TYPE_FIREBALL:
        scoreValue+=325;
        break;

    case TYPE_MAGNETIC_FIREBALL:
        scoreValue+=750;
        break;

    default:
        if(enemy->type==TYPE_BULLET)
            return 110;
        
        else if (enemy->type==TYPE_MINELAYER)
            return 1000;
        else
            printf("Error in getScoreValue : Unknown type\n");
        break;
    }

    if(enemy->size==SIZE_SMALL)
        scoreValue*=2;
    else if (enemy->size==SIZE_MEDIUM)
        scoreValue+=35;        
    return scoreValue;
}

Size generateRandomSize()
{
        
    switch (GetRandomValue(0,2))
    {
        case 0:
            return SIZE_SMALL;
        case 1:
            return SIZE_MEDIUM;
        default:
            return SIZE_LARGE;
    }

}

