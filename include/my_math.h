#pragma once
#include <stdio.h>
#include <math.h>

typedef struct Vector_2
{
    float x;
    float y;
} Vector_2;

static float racine_carre(float a)
{
    return sqrt(a);
}

static float puissance(float a, float puissance)
{
    for (int i = 1; i < puissance; i++)
    {
        a *= a;
    }
    return a;
}

static float my_cos(float a)
{
    return cos(a);
}

static float my_arccos(float a)
{
    return acos(a);
}

static float my_sin(float a)
{
    return sin(a);
}

static float valeur_absolue(float a)
{
    if (a < 0)
    {
        a *= -1;
    }
    return a;
}

static float determinant_matrice(Vector_2 a, Vector_2 b)
{
    float c = a.x * b.y - a.y * b.x;
    return c;
}

static float produit_scalaire(Vector_2 a, Vector_2 b)
{
    float c = a.x * b.x + a.y * b.y;
    return c;
}

static float normVector(Vector_2 a)
{
    float norm = sqrt(puissance(a.x, 2.f) + puissance(a.y, 2.f));    

    return norm;
}

static Vector_2 addVector(Vector_2 a, Vector_2 b)
{
    Vector_2 c = {a.x + b.x, a.y + b.y};
    return c;
}

static Vector_2 multiplyVector(Vector_2 a, float b)
{
    Vector_2 c = {a.x * b, a.y * b};
    return c;
}

static Vector_2 createVector(Vector_2 a, Vector_2 b)
{
    Vector_2 c = {b.x - a.x, b.y - a.y};
    return c;
}

static Vector_2 getNormalVector(Vector_2 a)
{
    Vector_2 b = {a.y, - a.x};
    return b;
}

static Vector_2 getProjection(Vector_2 normal, Vector_2 vertex, Vector_2 first)
{
    Vector_2 v = createVector(vertex, first);
    Vector_2 a = multiplyVector(normal, produit_scalaire(normal,v)/ produit_scalaire(normal,normal));
    return a;
}

static void getFurtherVertexesInRect(Vector_2 returnTable[2], Vector_2 vertexTable[4])
{
    Vector_2 temoinMax = {0,0};
    Vector_2 temoinMin = {0,0};
    for (int i = 0; i < 4; i++)
    {
        if (vertexTable[i].x > temoinMax.x)
        {
            temoinMax = vertexTable[i];
        }
        else if (vertexTable[i].x < temoinMin.x)
        {
            temoinMin = vertexTable[i];
        }
        else if (vertexTable[i].y > temoinMax.y)
        {
            temoinMax = vertexTable[i];
        }
        else if (vertexTable[i].y < temoinMin.y)
        {
            temoinMin = vertexTable[i];
        }
    }

    returnTable[0] = temoinMax;
    returnTable[1] = temoinMin; 

}

static void getFurtherVertexesInTriangle(Vector_2 returnTable[2], Vector_2 vertexTable[3])
{
    Vector_2 temoinMax = {0,0};
    Vector_2 temoinMin = {0,0};
    for (int i = 0; i < 3; i++)
    {
        if (vertexTable[i].x > temoinMax.x)
        {
            temoinMax = vertexTable[i];
        }
        else if (vertexTable[i].x < temoinMin.x)
        {
            temoinMin = vertexTable[i];
        }
        else if (vertexTable[i].y > temoinMax.y)
        {
            temoinMax = vertexTable[i];
        }
        else if (vertexTable[i].y < temoinMin.y)
        {
            temoinMin = vertexTable[i];
        }
    }

    returnTable[0] = temoinMax;
    returnTable[1] = temoinMin; 

}

static float degToRad(float angle)
{
    angle *= PI/180;
    return angle;
}

static float radToDeg(float angle)
{
    angle *= 180/PI;
    return angle;
}


static Vector_2 rotateVertex(Vector_2 vertex, Vector_2 origin, float angle)
{
    Vector_2 vertex2;

    vertex2.x = my_cos(angle) * (vertex.x - origin.x) - my_sin(angle) * (vertex.y - origin.y) + origin.x;
    vertex2.y = my_sin(angle) * (vertex.x - origin.x) + my_cos(angle) * (vertex.y - origin.y) + origin.y;

    return vertex2;
}

static Vector_2 getVectorFromClosestVertexToCenter(Vector_2 circleCenter, Vector_2 vertexTable[4])
{
    float normTemoin = 1000;
    Vector_2 vectorClosestVertexCenter = {};
    for (int i = 0; i < 4; i++)
    {
        Vector_2 vectorCenterVertex = createVector(circleCenter, vertexTable[i]);
        float norm = normVector(vectorCenterVertex);

        if (norm < normTemoin)
        {
            normTemoin = norm;
            vectorClosestVertexCenter = vertexTable[i];
        }
    }

    Vector_2 result = getNormalVector(vectorClosestVertexCenter);

    return result;
}

static Vector_2 getCirclePointFromVector(Vector_2 direction, Vector_2 center, float radius)
{
    Vector_2 u = {0, radius};
    float angle = my_arccos(
        produit_scalaire(u,direction) / (normVector(direction) * normVector(u))
    );

    Vector_2 m = {
        center.x + radius * my_cos(angle),
        center.y + radius * my_sin(angle)
    };

    return m;
}

static Vector_2 getReverseVector(Vector_2 a)
{
    Vector_2 b = {- a.x, - a.y};
    return b;
}

static Vector_2 getSmallestVector(Vector_2 a, Vector_2 b)
{
    if (normVector(a) < normVector(b))
        return a;
    return b;
}