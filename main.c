#include <stdio.h>
#include "sweep-line.h"
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "sets.h"

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

    int n = 10;
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
        printf("Point: (%f, %f)\n", points[i].x, points[i].y);
    }

    printf("Se generaron los %d puntos:\n", n);

    Point closestPair_sl[2];

    time_t start_sl, end_sl;
    double diff_sl, diff_2;
    double distance_sl;

    printf("Inicio sweepline\n");
    start_sl = time(NULL);
    sweepline(points, n, closestPair_sl, &distance_sl);
    end_sl = time(NULL);
    printf("Termino sweepline\n");

    diff_sl = difftime(end_sl, start_sl);
    printf("Tiempo de ejecucion sweepline: %.*lf\n", DBL_DIG, diff_sl);

    printf("Closest Pair: (%.*lf, %.*lf) and (%.*lf, %.*lf)\n with distance %.*lf\n",
           DBL_DIG, closestPair_sl[0].x, DBL_DIG, closestPair_sl[0].y,
           DBL_DIG, closestPair_sl[1].x, DBL_DIG, closestPair_sl[1].y,
           DBL_DIG, distance_sl);

    printf("Inicio closest\n");
    time_t start_closest = time(NULL);
    ClosestPair pair = closest(points, n);
    time_t end_closest = time(NULL);
    printf("Termino closest\n");

    double diff_closest = difftime(end_closest, start_closest);
    printf("Tiempo de ejecución closest: %.*lf segundos\n", DBL_DIG, diff_closest);

    printf("Closest Pair: (%.*lf, %.*lf) y (%.*lf, %.*lf) con distancia %.*lf\n",
           DBL_DIG, pair.point1.x, DBL_DIG, pair.point1.y,
           DBL_DIG, pair.point2.x, DBL_DIG, pair.point2.y,
           DBL_DIG, pair.distance);

    printf("Last two points: (%.*lf, %.*lf) y (%.*lf, %.*lf)",
           DBL_DIG, points[0].x, DBL_DIG, points[0].x,
           DBL_DIG, points[1].x, DBL_DIG, points[1].x);

    free(points);

    return 0;
}
