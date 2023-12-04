#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
//#include "sets.h" // Asegúrate de que este archivo define correctamente la estructura Set y sus funciones asociadas
#include <stdbool.h>

#include "both.h"
#define EPSIL 0.0000000001

typedef struct
{
    double distance;
    Point point1, point2;
} ClosestPair;


int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

bool arePointsEqual(Point p1, Point p2)
{
    return (p1.x == p2.x) && (p1.y == p2.y);
}

ClosestPair bruteForce(Point P[], int n)
{
    double minDist = DBL_MAX;
    ClosestPair minPair = {DBL_MAX, {0, 0}, {0, 0}};

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (P[i].x == P[j].x && P[i].y == P[j].y)
            {
                continue; // Ignora si los puntos son idénticos
            }
            double dist = calculateDistance(P[i], P[j]);
            if (dist < minDist)
            {
                minDist = dist;
                minPair = (ClosestPair){dist, P[i], P[j]};
            }
        }
    }
    return minPair;
}

ClosestPair stripClosest(Point strip[], int size, double d)
{
    double min = d;
    ClosestPair minPair = {d, {0, 0}, {0, 0}};

    qsort(strip, size, sizeof(Point), compareY);

    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
        {
            if (strip[i].x == strip[j].x && strip[i].y == strip[j].y)
            {
                continue; // Ignora si los puntos son idénticos
            }
            double dist = calculateDistance(strip[i], strip[j]);
            if (dist < min)
            {
                min = dist;
                minPair = (ClosestPair){dist, strip[i], strip[j]};
            }
        }
    }

    return minPair;
}

ClosestPair closestUtil(Point P[], int n)
{
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    ClosestPair dl = closestUtil(P, mid);
    ClosestPair dr = closestUtil(P + mid, n - mid);

    ClosestPair d = (dl.distance < dr.distance) ? dl : dr;

    Point *strip = malloc(n * sizeof(Point));

    if (strip == NULL)
    {
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(P[i].x - midPoint.x) < d.distance)
            strip[j++] = P[i];

    ClosestPair stripPair = stripClosest(strip, j, d.distance);
    if (stripPair.distance < d.distance)
        d = stripPair;

    free(strip);

    return d;
}

ClosestPair closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compareX);
    return closestUtil(P, n);
}


void sweepline(Point *points, int numPoints, Point *closestPair)
{
    ClosestPair pair = closest(points, numPoints);
    closestPair[0] = pair.point1;
    closestPair[1] = pair.point2;
}