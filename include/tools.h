#pragma once

#include "init.h"
#include <string.h>

Vector_2 generateRandomDirection();
Vector_2 generateRandomPosition();
Type generateRandomType();
Size generateRandomSize();
int getScoreValue(Enemy* enemy);
void createNewEnemy(Game* game, Type type, Size size, Vector_2 position, Vector_2 direction);
void createNewSpawn(Game* game, Type type, Vector_2 position);
Vector_2 magneticEffect(Game* game, Enemy* enemy);

