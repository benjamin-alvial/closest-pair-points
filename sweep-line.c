#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "both.h"

int comparePoints(const void *a, const void *b)
{
    double x1 = ((Point *)a)->x;
    double x2 = ((Point *)b)->x;

    if (x1 < x2)
        return -1;
    else if (x1 > x2)
        return 1;
    else
        return 0;
}

void sweepline(Point *points, int numPoints, Point *closestPair)
{
    qsort(points, numPoints, sizeof(Point), comparePoints);

    double minDistance = DBL_MAX;

    for (int i = 0; i < numPoints - 1; i++)
    {
        double distance = calculateDistance(points[i], points[i + 1]);

        if (distance < minDistance)
        {
            minDistance = distance;
            closestPair[0] = points[i];
            closestPair[1] = points[i + 1];
        }
    }
}
