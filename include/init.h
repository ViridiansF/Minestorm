#pragma once

// Les fonctions de init.c ne sont appelées qu'une fois par entité et initialisent ces entités
// De plus, init.c charge les ressources
#pragma once
#include <raylib.h>
#include<stdbool.h>
#include "my_math.h"
#include "draw.h"


#define SCREEN_WIDTH 640 * 1.7
#define SCREEN_HEIGHT 800 * 1.7

#define MAX_BULLET 50
#define MAX_ENEMIES 150
#define MAX_SPAWNS 300

#define PLAYER_WIDTH 42
#define PLAYER_HEIGHT 70

#define MINELAYER_WIDTH 255 
#define MINELAYER_HEIGHT 126

#define STARTING_ENEMY_NUMBER 1
#define SPAWNING_TIME 3

#define NUMBER_ENEMY_SPRITE 7
#define NUMBER_SOUND_EFFECT 5

typedef struct Bullet
{
    Vector_2 position;
    Vector_2 direction;
    float radius;              // Détermine le rayon de la balle
    float distanceTravelled;  // Indique la distance parcourue par la balle, utilisé dans la fonction de suppression des balles
    float speed;
    Texture2D sprite;
    bool hasCollided;
} Bullet;


typedef enum Size
{
    SIZE_BULLET=30,
    SIZE_SMALL=40,
    SIZE_MEDIUM=60,
    SIZE_LARGE=80,
} Size;

typedef enum SoundId
{
    PLAYER_GUN,
    PLAYER_DEATH,
    PLAYER_TELEPORATION,
    PLAYER_CRITICALHULL,
    ENEMY_HIT,
} SoundId;



typedef enum GameStatus
{
    NOT_STARTED,
    RUNNING,
    PAUSED,
    OVER,
}GameStatus;

typedef enum Type
{
    TYPE_FLOATING,                  //  Type de base, flotte lentement dans sa direction. Est de forme triangulaire
    TYPE_FIREBALL,                //  Type avancé, flotte lentement dans sa direction en tirant des balles vers le joueur. Est de forme carré
    TYPE_MAGNETIC,                //  Type avancé, flotte vers le joueur. Est de forme carré
    TYPE_MAGNETIC_FIREBALL,     //  Type combiné, flotte vers le joueur en tirant des balles. Est de forme carré
    TYPE_MINELAYER,             //  Boss, rajoute des spawns quand il n'y en a plus. Peut-être détruit mais a plusieurs pv
    TYPE_BULLET,                     //  Type projectile, est projetté par les ennemis bombardiers    
    TYPE_SPAWN,
} Type;


typedef struct Player
{
    int playerId;
    int bulletCount;
    Bullet bullets[MAX_BULLET];
    Vector_2 position;
    float speed;
    Vector_2 direction;

    float angle;
    int hp;
    Texture2D sprite;
    float invincibilityTimer;
    
    int score;


    Sound* se[NUMBER_SOUND_EFFECT-1];


} Player;


typedef struct Enemy
{
    Type type;
    Size size;
    Vector_2 position;
    Vector_2 direction;
    int hp;
    int scoreValue;
    Texture2D* sprite;
    float timer;                // Used by Fireball enemies to delay their shots
} Enemy;


typedef struct Spawn
{
    Type type;
    Vector_2 position;
    Texture2D* sprite;
} Spawn;


typedef struct Game
{
    int enemyCount;
    Enemy enemies[MAX_ENEMIES];

    int playerCount;
    Player players[2];

    int spawnCount;
    Spawn spawns[MAX_SPAWNS];

    Texture2D foreground;
    Texture2D background;
    Texture2D logo;

    Texture2D enemiesSprites[NUMBER_ENEMY_SPRITE];
    float gameTimer;

    GameStatus gameStatus;
    Music music;
    Music titleMusic;
    Music gameOverMusic;
    Music victoryMusic;


    Sound se[NUMBER_SOUND_EFFECT];


    Enemy minelayer;
    bool minelayerIsOnScreen;
    
    int difficulty;

    bool visibleHiboxes;

} Game;

#include "tools.h"


// Entity initalization functions
void initGame(Game* game);         
void restartGame(Game* game);
void initPlayer(Player* player, Vector_2 position); 


// Loading assets
void loadTextures(Game* game);
void loadMusic();


// Unloading assets
void unloadGameTextures(Game* game);
void unloadGameMusic(Game* game);
