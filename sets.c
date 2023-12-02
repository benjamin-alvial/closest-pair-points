#include <stdio.h>
#include <stdlib.h>
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
