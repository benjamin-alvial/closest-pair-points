#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "both.h"

#include <stdbool.h>

typedef struct
{
    Point *members;
    int length;
} Set;

Set *init();
bool is_member(Set *set, Point value);
void insert(Set *set, Point member);
void print_set(Set *set);
Set *set_intersection(Set *setA, Set *setB);

Set *init()
{
    Set *new_set = malloc(sizeof(Set));
    if (new_set == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new_set->length = 0;
    new_set->members = malloc(sizeof(Point));
    if (new_set->members == NULL)
    {
        free(new_set);
        exit(EXIT_FAILURE);
    }
    return new_set;
}

bool is_member(Set *set, Point value)
{
    for (int i = 0; i < set->length; i++)
        if (set->members[i].x == value.x && set->members[i].y == value.y)
            return true;
    return false;
}

void insert(Set *set, Point member)
{
    if (!is_member(set, member))
    {
        Point *temp = realloc(set->members, sizeof(Point) * (set->length + 1));
        if (temp == NULL)
        {
            free(set->members);
            exit(EXIT_FAILURE);
        }
        set->members = temp;
        set->members[set->length] = member;
        set->length++;
    }
}

void print_set(Set *set)
{
    for (int i = 0; i < set->length; i++)
    {
        printf("(%f, %f)", set->members[i].x, set->members[i].y);
        if (i < set->length - 1)
            printf(", ");
    }
    printf("\n");
}

Set *set_intersection(Set *setA, Set *setB)
{
    if (setA == NULL || setB == NULL)
    {
        return NULL;
    }

    Set *new = init();
    if (new == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < setA->length; i++)
    {
        if (is_member(setB, setA->members[i]))
        {
            insert(new, setA->members[i]);
        }
    }
    return new;
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
