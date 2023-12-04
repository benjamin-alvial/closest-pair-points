#ifndef SETS_H
#define SETS_H

#include <stdbool.h>

typedef struct
{
    double x, y;
} Point;

typedef struct
{
    Point *members;
    int length;
} Set;

typedef struct
{
    double distance;
    Point point1, point2;
} ClosestPair;

Set *init();
bool is_member(Set *set, Point value);
void insert(Set *set, Point member);
void print_set(Set *set);
Set *set_intersection(Set *setA, Set *setB);

#endif /* SETS_H */
