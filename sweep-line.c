#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "sets.h" // Asegúrate de que este archivo define correctamente la estructura Set y sus funciones asociadas

double calculateDistance(Point p1, Point p2)
{
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

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

void sweepline(Point *points, int numPoints, Point *closestPair, double *dist)
{
    qsort(points, numPoints, sizeof(Point), compareX);

    double d = DBL_MAX;
    Set *set = init();
    if (set == NULL)
    {
        return;
    }

    insert(set, points[0]);

    for (int i = 1; i < numPoints; ++i)
    {
        Set *l = init();
        Set *r = init();
        if (l == NULL || r == NULL)
        {
            free(set->members);
            free(set);
            if (l != NULL)
            {
                free(l->members);
                free(l);
            }
            if (r != NULL)
            {
                free(r->members);
                free(r);
            }
            return;
        }

        for (int k = 0; k < set->length; k++)
        {
            if ((set->members[k].x >= points[i].x - d) && (set->members[k].y >= points[i].y - d))
            {
                insert(l, set->members[k]);
            }
            if ((set->members[k].x <= points[i].x + d) && (set->members[k].y <= points[i].y + d))
            {
                insert(r, set->members[k]);
            }
        }

        Set *intersection = set_intersection(l, r);
        if (intersection == NULL || intersection->length == 0)
        {
            free(l->members);
            free(l);
            free(r->members);
            free(r);
            if (intersection != NULL)
            {
                free(intersection->members);
                free(intersection);
            }
            continue;
        }

        for (int j = 0; j < intersection->length; j++)
        {
            double distance = calculateDistance(points[i], intersection->members[j]);
            if (distance < d)
            {
                d = distance;
                *dist = d;
                closestPair[0] = points[i];
                closestPair[1] = intersection->members[j];
            }
        }

        insert(set, points[i]);

        free(intersection->members);
        free(intersection);
        free(l->members);
        free(l);
        free(r->members);
        free(r);
    }

    free(set->members);
    free(set);

    /*

    bool foundFirst = false, foundSecond = false;
    for (int i = 0; i < numPoints; i++)
    {
        if (arePointsEqual(points[i], closestPair[0]))
        {
            foundFirst = true;
        }
        if (arePointsEqual(points[i], closestPair[1]))
        {
            foundSecond = true;
        }
    }

    if (!foundFirst || !foundSecond)
    {
        printf("Uno o ambos puntos del par mas cercano no se encontraron en el arreglo original.\n");
    }
    else
    {
        printf("Ambos puntos del par mas cercano se encontraron en el arreglo original.\n");
    }
    */
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
