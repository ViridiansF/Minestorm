#pragma once

#include <raylib.h>
#include "init.h"

// Les fonctions de draw.c ne font que dessiner sur l'écran

typedef struct my_Circle
{
    Vector_2 center;
    float radius;
}my_Circle;

typedef struct my_Triangle
{
    Vector_2 vertexTable[3];
    Vector_2 center;
    float radius;

    Vector_2 directorVector[3];
    Vector_2 normalVector[3];
}my_Triangle;

typedef struct my_Rectangle
{
    Vector_2 vertexTable[4];
    Vector_2 center;
    float radius;

    Vector_2 directorVector[2];
    Vector_2 normalVector[2];

}my_Rectangle;

void drawGame();
void drawTitleScreen();
void drawPauseMenu();
void drawGameOver();


void drawPause();

void drawPlayer();
void drawEnemy();
void drawBullet();

void drawBackground();
void drawBorders();
void drawUI();

void introCinematic();

void drawMinelayer();
void drawNewHitBoxes(my_Rectangle rectangle1);
my_Rectangle entityToRectangle(Vector_2 position, float width, float height,float angle);
my_Rectangle createRectangle(Vector_2 origin, Vector_2 secondVertex, Vector_2 thirdVertex, Vector_2 fourthVertex);
void drawPlayerHitBox();
