#include <stdio.h>
#include "sweep-line.h"
#include <stdlib.h>
#include <time.h>
#include <float.h>

double randomZeroToOne()
{
    return (double)rand() / (RAND_MAX + 1.0);
}

Point generateRandomPoint()
{
    Point randomPoint;
    randomPoint.x = randomZeroToOne();
    randomPoint.y = randomZeroToOne();
    return randomPoint;
}

int main()
{
    printf("Creacion random seed:\n");
    srand((unsigned int)time(NULL));

    int n = 50000000;
    printf("n: %d\n", n);

    Point *points = (Point *)malloc(n * sizeof(Point));

    if (points == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Generando %d random points:\n", n);
    for (int i = 0; i < n; i++)
    {
        points[i] = generateRandomPoint();
        // printf("Point: (%f, %f)\n", points[i].x, points[i].y);
    }

    printf("Se generaron los %d puntos:\n", n);

    Point closestPair[2];

    time_t start, end;
    double diff;

    printf("Inicio sweepline\n");
    start = time(NULL);
    sweepline(points, n, closestPair);
    end = time(NULL);
    printf("Termino sweepline\n");

    diff = difftime(end, start);
    printf("Tiempo de ejecucion: %.*lf\n", DBL_DIG, diff);

    printf("Closest Pair: (%.*lf, %.*lf) and (%.*lf, %.*lf)\n",
           DBL_DIG, closestPair[0].x, DBL_DIG, closestPair[0].y,
           DBL_DIG, closestPair[1].x, DBL_DIG, closestPair[1].y);

    free(points);

    return 0;
}
