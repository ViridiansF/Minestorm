# Minestorm

Minestorm est un jeu d'arcade où le but et d'obtenir le meilleur score possible en détruisant les mines posées par le Vaisseau Mère.
Dans cette version il est possible d'obtenir la victoire en abattant le Vaisseau Mère. Pour le faire appraitre il faut détruire les mines qu'il pose.

Il y a tout de même un système de score pour les joueurs les plus compétitifs.

Cette version est réalisée par Antoine Mordant et Maël Jammet avec la librairie graphique Raylib.
___
# Comment jouer ?

## Accélérer : 
- Joueur 1 : 'R'
- Joueur 2 : 'I'

## Pivoter : 
- Joueur 1 : 'S' (gauche), 'F' (droite)
- Joueur 2 : 'J' (gauche), 'L' (droite)

## Tirer : 
- Joueur 1 : 'F' 
- Joueur 2 : 'K'

## Pause :
- 'Espace'

## Quitter :
- 'Echap'

## Afficher les Hitbox :
- 'C'

___
# Structure du code

## Fichiers

### main

- Appelle les autres fonctions, 
- Contient la boucle de raylib permettant de dessiner,
- Ouvre la fenêtre,

### init

- Initilise les objets,
- Charge les textures,
- Charge les musiques

### gameController

- Premier fichier exécuté,
- Vérifie l'état du jeu pour le diriger vers les fonctions appropriées,

### update

- Met à jour les différents objets du jeu,
- Appelle les fonctions de vérification des collisions,

### draw

- Dessine tous les objets du jeu,
- Contient des fonctions permettant de générer des formes à partir d'un ensemble de points,

### my_math

- Librairie mathématique personnelle utilisée notamment par les fonctions de collision
- Contient de nombreuses fonctions permettant de manipuler les points et les vecteurs, 

### collisions

- Contient les fonctions de collision

### tools 

- Contient différentes fonctions utiles dans tout le code 
___
# Structures

## Game

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
    Music playerEngineMusic;
    Music victoryMusic;


    SoundEffect se[NUMBER_SOUND_EFFECT];


    Enemy minelayer;
    bool minelayerIsOnScreen;
    
    int difficulty;

    bool visibleHiboxes;

    } Game;

Structure principale du jeu. Elle contient toutes les informations permettant le déroulement du jeu.

Notamment :
- Un tableau d'ennemis,
- Un tableau de joueurs,
- Un tableau de textures,
- Un tableau de sons,
- Les musiques,

## Spawm

    typedef struct Spawn
    {
    Type type;
    Vector_2 position;
    Texture2D* sprite;
    } Spawn;

Le Vaisseau Mère crée des spawns qui deviennent ensuite des ennemis.

## Enemy

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

Structure représentant une mine dans le jeu.
Chaque mine possède un timer qui n'est utilisé que pour les ennemis de type FIREBALL afin de générer un délai entre les tirs de ces ennemis.


## Player

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

    SoundEffect* shipGunSound;
    SoundEffect* teleportationSound;
    SoundEffect* deathSound;
    Music* engineSound;


    } Player;

Structure représentant un joueur.
Contient notamment un tableau de balles permettant la gestion différenciée des balles de chaque joueurs.

## Bullet

    typedef struct Bullet
    {
    Vector_2 position;
    Vector_2 direction;
    float radius;              
    float distanceTravelled;  
    float speed;
    Texture2D sprite;
    bool hasCollided;
    } Bullet;

Structure représentant une balle.
Les balles stockent la distance qu'elle parcours. Cela permet de les supprimer quand elle a parcouru sa distance maximale.

___
# Crédits

## Musiques
- Écran titre : "Open a Breach" - Into the Breach
- Musique pendant le jeu : "A.C.I.D" - Into the Breach
- Game Over : "Sun Station" - Outer Wilds
- Victoire : "Region Secured" - Into the Breach

## Sons
- Chaine Youtube Seaguli

## Sprites
- Corps enseignant de l'Isart

## Code
- Écrit par Antoine Mordant et Maël Jammet à l'aide de la librairie Raylib