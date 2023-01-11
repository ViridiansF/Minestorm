#include "../include/collisions.h"

my_Triangle createTriangle(Vector_2 origin, Vector_2 secondVertex, Vector_2 thirdVertex)
{
    
    my_Triangle triangle;

    triangle.vertexTable[0]=origin;
    triangle.vertexTable[1]=secondVertex;
    triangle.vertexTable[2]=thirdVertex;

    triangle.center = origin;

    triangle.directorVector[0]=createVector(triangle.vertexTable[0],triangle.vertexTable[1]);
    triangle.directorVector[1]=createVector(triangle.vertexTable[1],triangle.vertexTable[2]);
    triangle.directorVector[1]=createVector(triangle.vertexTable[2],triangle.vertexTable[0]);


    triangle.normalVector[0]=getNormalVector(triangle.directorVector[0]);
    triangle.normalVector[1]=getNormalVector(triangle.directorVector[1]);
    triangle.normalVector[1]=getNormalVector(triangle.directorVector[2]);


    float radius = 0;
    for (int i = 0; i < 3; i++)
    {   
        Vector_2 radiusTry = {triangle.vertexTable[i].x - triangle.center.x, triangle.vertexTable[i].y - triangle.center.y};
        if (normVector(radiusTry) > radius)
        {
            radius = normVector(radiusTry);
        }
    }
    triangle.radius=radius;

    return triangle; 
    
}

bool collisionCircleCircle(Vector_2 posCircle1, int radiusCircle1, Vector_2 posCircle2,int radiusCircle2)
{
    Vector_2 centerCenterVector = {posCircle1.x - posCircle2.x, posCircle1.y - posCircle2.y};
    float normCenterCenterVector = normVector(centerCenterVector);
    if (normCenterCenterVector <= radiusCircle1 + radiusCircle2)
    {
        return true;
    }
    return false;
}

bool collisionEnemyPlayer(Enemy* enemy, Player* player)
{
    my_Rectangle playerHitbox=entityToRectangle(player->position,PLAYER_WIDTH,PLAYER_HEIGHT,0);

    if(enemy->type==TYPE_FLOATING)
    {
        Vector_2 enemyVertex[3];
        enemyVertex[0]=enemy->position;
        
        enemyVertex[1].x=enemy->position.x+ enemy->size;
        enemyVertex[1].y=enemy->position.y;
        
        enemyVertex[2].x=enemy->position.x + enemy->size / 2 ;
        enemyVertex[2].y=enemy->position.y + enemy->size;

        my_Triangle enemyHitbox = createTriangle(enemyVertex[0],enemyVertex[1],enemyVertex[2]);

        return collisionRectangleTriangle(playerHitbox,enemyHitbox);
    }
    else if (enemy->type == TYPE_BULLET)
    {
        return collisionBulletPlayer(enemy, player);
    }
    else
    {
        my_Rectangle enemyHitbox=entityToRectangle(enemy->position,enemy->size,enemy->size,0);

        return collisionRectangleRectangle(playerHitbox,enemyHitbox);
    }

    return false;
    
}

bool collisionRectangleTriangle(my_Rectangle rectangle, my_Triangle triangle)
{
    if(collisionCircleCircle(rectangle.center,rectangle.radius,triangle.center,triangle.radius))
    {
        
        Vector_2 normalVectorTable[5] = {
            rectangle.normalVector[0],
            rectangle.normalVector[1],
            triangle.normalVector[0],
            triangle.normalVector[1],
            triangle.normalVector[2],
        };

        for(int i=0;i<5;i++)
        {
            int h = i;
            Vector_2 firstProjection = addVector
            (
                rectangle.vertexTable[h],
                multiplyVector(rectangle.directorVector[h],2.0f)
            );
            if (i >= 2)
            {
                h = i - 2;
                firstProjection = addVector
                (
                    triangle.vertexTable[h],
                    multiplyVector(triangle.directorVector[h],2.0f)
                );
            }


            Vector_2 projectionRectangle[4];
            Vector_2 projectionTriangle[3];
        
            
            // In reference to Rectangle
            for(int j=0;j<4;j++)
            {
                projectionRectangle[j]=getProjection(normalVectorTable[i],rectangle.vertexTable[j],firstProjection);
                if (j < 3)
                    projectionTriangle[j]=getProjection(normalVectorTable[i],triangle.vertexTable[j],firstProjection);
            }

            Vector_2 farthestTwoVertexRectangle[2];
            Vector_2 farthestTwoVertexTriangle[2];

            getFurtherVertexesInRect(farthestTwoVertexRectangle,projectionRectangle);
            getFurtherVertexesInTriangle(farthestTwoVertexTriangle,projectionTriangle);

            Vector_2 vectorRectangleFarthestVertex = createVector(farthestTwoVertexRectangle[0],farthestTwoVertexRectangle[1]);
            Vector_2 vectorRectangleand2FarthestVertex = createVector(farthestTwoVertexRectangle[0],farthestTwoVertexTriangle[0]);


            Vector_2 vectorTriangleFarthestVertex = createVector(farthestTwoVertexTriangle[0],farthestTwoVertexTriangle[1]);
            Vector_2 vectorTriangleand1FarthestVertex = createVector(farthestTwoVertexTriangle[0],farthestTwoVertexRectangle[0]);

            float security = determinant_matrice(vectorRectangleFarthestVertex, vectorTriangleFarthestVertex);
            if(security > 0.001f || security < -0.001f)
            {
                printf("OSKOUR\n");
                return false;
            }

            if(normVector(vectorRectangleFarthestVertex)<normVector(vectorRectangleand2FarthestVertex))
            {
                if(normVector(vectorTriangleFarthestVertex)<normVector(vectorTriangleand1FarthestVertex))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool collisionRectangleRectangle(my_Rectangle rectangle1, my_Rectangle rectangle2)
{

    if(collisionCircleCircle(rectangle1.center,rectangle1.radius,rectangle2.center,rectangle2.radius))
    {
        
        Vector_2 normalVectorTable[4] = {
            rectangle1.normalVector[0],
            rectangle1.normalVector[1],
            rectangle2.normalVector[0],
            rectangle2.normalVector[1],
        };

        for(int i=0;i<4;i++)
        {
            my_Rectangle rectangle = rectangle1;
            int h = i;
            if (i >= 2)
            {
                rectangle = rectangle2;
                h = i - 2;
            }


            Vector_2 firstProjection = addVector
            (
                rectangle.vertexTable[h],
                multiplyVector(rectangle.directorVector[h],2.0f)
            );


            Vector_2 projectionRectangle1[4];
            Vector_2 projectionRectangle2[4];
        
            
            // In reference to rectangle1
            for(int j=0;j<4;j++)
            {
                projectionRectangle1[j]=getProjection(normalVectorTable[i],rectangle1.vertexTable[j],firstProjection);
                projectionRectangle2[j]=getProjection(normalVectorTable[i],rectangle2.vertexTable[j],firstProjection);
            }

            Vector_2 farthestTwoVertexRectangle1[2];
            Vector_2 farthestTwoVertexRectangle2[2];

            getFurtherVertexesInRect(farthestTwoVertexRectangle1,projectionRectangle1);
            getFurtherVertexesInRect(farthestTwoVertexRectangle2,projectionRectangle2);

            Vector_2 vectorRectangle1FarthestVertex = createVector(farthestTwoVertexRectangle1[0],farthestTwoVertexRectangle1[1]);
            Vector_2 vectorRectangle1and2FarthestVertex = createVector(farthestTwoVertexRectangle1[0],farthestTwoVertexRectangle2[0]);

            Vector_2 vectorRectangle2FarthestVertex = createVector(farthestTwoVertexRectangle2[0],farthestTwoVertexRectangle2[1]);
            Vector_2 vectorRectangle2and1FarthestVertex = createVector(farthestTwoVertexRectangle2[0],farthestTwoVertexRectangle1[0]);

            float security = determinant_matrice(vectorRectangle1FarthestVertex, vectorRectangle2FarthestVertex);
            if(security > 0.001f || security < -0.001f)
            {
                printf("OSKOUR\n");
                return false;
            }


            if(normVector(vectorRectangle1FarthestVertex)<normVector(vectorRectangle1and2FarthestVertex))
            {
                if(normVector(vectorRectangle2FarthestVertex)<normVector(vectorRectangle2and1FarthestVertex))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

my_Circle createCircle(Vector_2 center, float radius)
{
    
    my_Circle circle;
    circle.center = center;
    circle.radius = radius;
    return circle;
    
}

bool collisionBulletEnemy(Bullet* bullet, Enemy* enemy)
{
    
    my_Circle circle = createCircle(bullet->position, bullet->radius);

    if(enemy->type==TYPE_MINELAYER)
    {
        Vector_2 enemyVertex[4];
        enemyVertex[0]=enemy->position;
        
        enemyVertex[1].x=enemy->position.x+255;
        enemyVertex[1].y=enemy->position.y;
        
        enemyVertex[2].x=enemy->position.x + 255;
        enemyVertex[2].y=enemy->position.y + 126;

        enemyVertex[3].x=enemy->position.x;
        enemyVertex[3].y=enemy->position.y+126;

    
        my_Rectangle enemyHitbox = createRectangle(enemyVertex[0],enemyVertex[1],enemyVertex[2],enemyVertex[3]);
        return collisionCircleRectangle(circle,enemyHitbox);

       
    }
    else if(enemy->type==TYPE_FLOATING)
    {
        Vector_2 enemyVertex[3];
        enemyVertex[0]=enemy->position;
        
        enemyVertex[1].x=enemy->position.x+ enemy->size;
        enemyVertex[1].y=enemy->position.y;
        
        enemyVertex[2].x=enemy->position.x + enemy->size / 2 ;
        enemyVertex[2].y=enemy->position.y + enemy->size;

        my_Triangle enemyHitbox = createTriangle(enemyVertex[0],enemyVertex[1],enemyVertex[2]);

        return collisionCircleTriangle(circle,enemyHitbox);
    }
    else
    {
        Vector_2 enemyVertex[4];
        enemyVertex[0]=enemy->position;
        
        enemyVertex[1].x=enemy->position.x+ enemy->size;
        enemyVertex[1].y=enemy->position.y;
        
        enemyVertex[2].x=enemy->position.x + enemy->size;
        enemyVertex[2].y=enemy->position.y + enemy->size;

        enemyVertex[3].x=enemy->position.x;
        enemyVertex[3].y=enemy->position.y+enemy->size;

        my_Rectangle enemyHitbox = createRectangle(enemyVertex[0],enemyVertex[1],enemyVertex[2],enemyVertex[3]);

        return collisionCircleRectangle(circle,enemyHitbox);
    }
    
}

bool collisionBulletPlayer(Enemy* bullet, Player* player)
{
    
    my_Circle circle = createCircle(bullet->position, bullet->size/2);

    Vector_2 playerVertex[4];
    playerVertex[0]=player->position;
    
    playerVertex[1].x=player->position.x+ PLAYER_WIDTH;
    playerVertex[1].y=player->position.y;
    
    playerVertex[2].x=player->position.x + PLAYER_WIDTH;
    playerVertex[2].y=player->position.y + PLAYER_HEIGHT;

    playerVertex[3].x=player->position.x;
    playerVertex[3].y=player->position.y+PLAYER_HEIGHT;

    my_Rectangle playerHitbox = createRectangle(playerVertex[0],playerVertex[1],playerVertex[2],playerVertex[3]);

    return collisionCircleRectangle(circle, playerHitbox);
}

bool collisionCircleRectangle(my_Circle circle, my_Rectangle rectangle)
{
    if(collisionCircleCircle(rectangle.center,rectangle.radius,circle.center,circle.radius))
    {
        Vector_2 circleDirectionVector = getVectorFromClosestVertexToCenter(circle.center, rectangle.vertexTable);
        Vector_2 circleNormalVector = getNormalVector(circleDirectionVector);

        Vector_2 normalVectorTable[3] = {
            rectangle.normalVector[0],
            rectangle.normalVector[1],
            circleNormalVector,
        };

        for(int i=0;i < 3;i++)
        {
            Vector_2 circlePointTable[2] = {
                getCirclePointFromVector(normalVectorTable[i], circle.center, circle.radius),
                getCirclePointFromVector(getReverseVector(normalVectorTable[i]), circle.center, circle.radius)
                };

            int h = i;
            Vector_2 firstProjection = addVector
            (
                rectangle.vertexTable[h],
                multiplyVector(rectangle.directorVector[h],2.0f)
            );
            if (i >= 2)
            {
                h = i - 2;
                firstProjection = addVector(
                    circlePointTable[h],
                    multiplyVector(circleDirectionVector,2.0f)
                );
            }


            Vector_2 projectionRectangle[4];
            Vector_2 projectionCircle[2];
        
            
            // In reference to Rectangle
            for(int j=0;j<4;j++)
            {
                projectionRectangle[j]=getProjection(normalVectorTable[i],rectangle.vertexTable[j],firstProjection);
                if (j < 2)
                    projectionCircle[j]=getProjection(normalVectorTable[i],circlePointTable[j],firstProjection);
            }

            Vector_2 farthestTwoVertexRectangle[2];

            getFurtherVertexesInRect(farthestTwoVertexRectangle,projectionRectangle);


            Vector_2 vectorRectangleFarthestVertex = createVector(farthestTwoVertexRectangle[0],farthestTwoVertexRectangle[1]);
            Vector_2 vectorRectangleand2FarthestVertex = createVector(farthestTwoVertexRectangle[0],projectionCircle[0]);

            Vector_2 vectorCircleFarthestVertex = createVector(projectionCircle[0],projectionCircle[1]);
            Vector_2 vectorCircleand1FarthestVertex = createVector(projectionCircle[0],farthestTwoVertexRectangle[0]);

            float security = determinant_matrice(vectorRectangleFarthestVertex, vectorCircleFarthestVertex);
            if(security > 0.001f || security < -0.001f)
            {
                printf("OSKOUR\n");
                return false;
            }


            if(normVector(vectorRectangleFarthestVertex)<normVector(vectorRectangleand2FarthestVertex))
            {
                if(normVector(vectorCircleFarthestVertex)<normVector(vectorCircleand1FarthestVertex))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool collisionCircleTriangle(my_Circle circle, my_Triangle triangle)
{
    if(collisionCircleCircle(triangle.center,triangle.radius,circle.center,circle.radius))
    {
        Vector_2 circleDirectionVector = getVectorFromClosestVertexToCenter(circle.center, triangle.vertexTable);
        Vector_2 circleNormalVector = getNormalVector(circleDirectionVector);

        Vector_2 normalVectorTable[4] = {
            triangle.normalVector[0],
            triangle.normalVector[1],
            triangle.normalVector[2],
            circleNormalVector,
        };

        for(int i=0;i < 4;i++)
        {
            Vector_2 circlePointTable[2] = {
                getCirclePointFromVector(normalVectorTable[i], circle.center, circle.radius),
                getCirclePointFromVector(getReverseVector(normalVectorTable[i]), circle.center, circle.radius)
                };

            int h = i;
            Vector_2 firstProjection = addVector
            (
                triangle.vertexTable[h],
                multiplyVector(triangle.directorVector[h],2.0f)
            );
            if (i >= 3)
            {
                h = i - 3;
                firstProjection = addVector(
                    circlePointTable[h],
                    multiplyVector(circleDirectionVector,2.0f)
                );
            }


            Vector_2 projectionTriangle[3];
            Vector_2 projectionCircle[2];
        
            
            // In reference to Triangle
            for(int j=0;j<3;j++)
            {
                projectionTriangle[j]=getProjection(normalVectorTable[i],triangle.vertexTable[j],firstProjection);
                if (j < 2)
                    projectionCircle[j]=getProjection(normalVectorTable[i],circlePointTable[j],firstProjection);
            }

            Vector_2 farthestTwoVertexTriangle[2];

            getFurtherVertexesInTriangle(farthestTwoVertexTriangle,projectionTriangle);

            Vector_2 vectorTriangleFarthestVertex = createVector(farthestTwoVertexTriangle[0],farthestTwoVertexTriangle[1]);
            Vector_2 vectorTriangleand2FarthestVertex = createVector(farthestTwoVertexTriangle[0],projectionCircle[0]);

            Vector_2 vectorCircleFarthestVertex = createVector(projectionCircle[0],projectionCircle[1]);
            Vector_2 vectorCircleand1FarthestVertex = createVector(projectionCircle[0],farthestTwoVertexTriangle[0]);


            float security = determinant_matrice(vectorTriangleFarthestVertex, vectorTriangleFarthestVertex);
            if(security > 0.001f || security < -0.001f)
            {
                printf("OSKOUR\n");
                return false;
            }


            if(normVector(vectorTriangleFarthestVertex)<normVector(vectorTriangleand2FarthestVertex))
            {
                if(normVector(vectorCircleFarthestVertex)<normVector(vectorCircleand1FarthestVertex))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
