#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "sweep-line.c"

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

void closestPair(Point *points, int numPoints, Point *closestPairPoints)
{
    qsort(points, numPoints, sizeof(Point), compareX);

    double d = DBL_MAX;
    Point *strip = malloc(numPoints * sizeof(Point));

    if (!strip)
    {
        // Handle memory allocation failure
        exit(1);
    }

    for (int i = 0; i < numPoints; ++i)
    {
        // Consider points only within the strip of width 2d
        int stripCount = 0;
        for (int j = i + 1; j < numPoints && (points[j].x - points[i].x) < d; ++j)
        {
            strip[stripCount++] = points[j];
        }

        qsort(strip, stripCount, sizeof(Point), compareY);

        // Find the closest points in strip.
        for (int k = 0; k < stripCount; ++k)
        {
            for (int l = k + 1; l < stripCount && (strip[l].y - strip[k].y) < d; ++l)
            {
                double dist = calculateDistance(strip[k], strip[l]);
                if (dist < d)
                {
                    d = dist; // Update the minimum distance
                    // Update the closest pair
                    closestPairPoints[0] = strip[k];
                    closestPairPoints[1] = strip[l];
                }
            }
        }
    }

    free(strip);
}