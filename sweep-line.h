#ifndef SWEEP_LINE_H
#define SWEEP_LINE_H
#include "sets.h"

ClosestPair closest(Point *P, int n);
void sweepline(Point *points, int numPoints, Point *closestPair, double *dist);
ClosestPair closestB(Point P[], int n);

#endif
