#ifndef SWEEP_LINE_H
#define SWEEP_LINE_H

typedef struct
{
    double x, y;
} Point;

void sweepline(Point *points, int numPoints, Point *closestPair);

#endif
