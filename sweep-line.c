#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "sets.h"

double calculateDistance(Point p1, Point p2)
{
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    if (p1->x > p2->x)
    {
        return 1;
    }
    else if (p1->x < p2->x)
    {
        return -1;
    }
    return 0;
}

bool arePointsEqual(Point p1, Point p2)
{
    return (p1.x == p2.x) && (p1.y == p2.y);
}

void sweepline(Point *points, int numPoints, Point *closestPair)
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
