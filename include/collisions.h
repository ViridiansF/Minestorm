#pragma once
#include <raylib.h>
#include<stdbool.h>
#include "my_math.h"
#include "draw.h"




bool collisionSATCircleCircle(Vector_2 posCircle1, int radiusCircle1, Vector_2 posCircle2,int radiusCircle2);
bool collisionEnemyPlayer(Enemy* enemy, Player* player);
bool collisionRectangleTriangle(my_Rectangle rectangle, my_Triangle triangle);
bool collisionBulletEnemy(Bullet* bullet, Enemy* enemy);
bool collisionBulletPlayer(Enemy* bullet, Player* player);
bool collisionCircleRectangle(my_Circle circle, my_Rectangle rectangle);
bool collisionCircleTriangle(my_Circle circle, my_Triangle triangle);
bool collisionRectangleRectangle(my_Rectangle rectangle1, my_Rectangle rectangle2);
bool collisionCircleCircle(Vector_2 posCircle1, int radiusCircle1, Vector_2 posCircle2,int radiusCircle2);
