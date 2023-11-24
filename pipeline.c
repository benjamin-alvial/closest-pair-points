#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "sweep-line.c"
//#include "randomized.c"

// Values for amount of points.
// go from N_INITIAL to N_FINAL with steps of N_STEP
// #define N_INITIAL 5000000
// #define N_FINAL 50000000
// #define N_STEP 5000000
#define N_INITIAL 5000000
#define N_FINAL 50000000
#define N_STEP 5000000

// Amount of times the algorithm will be executed to calculate
// the average performance
// #define NUMBER_REPS 101
#define NUMBER_REPS 5

double randomZeroToOne() {
    return (double)rand() / (RAND_MAX + 1.0);
}

Point generateRandomPoint() {
    Point randomPoint;
    randomPoint.x = randomZeroToOne();
    randomPoint.y = randomZeroToOne();
    return randomPoint;
}

int main() {
    // Set the seed for testing and evaluation purposes.
    srand(123);

    // This file will be used to plot the performance data.
    FILE *results_file = fopen("performance_results.txt", "w");

    for(int n=N_INITIAL; n<N_FINAL+1; n+=N_STEP) {

        printf("--------------------------------------------\n");
        printf("Finding the closest pair from %d points for %d repetitions...\n", n, NUMBER_REPS);
        printf("--------------------------------------------\n");

        printf("- Creating array...\n");

        // Generate array of n points.
        Point *points = (Point *)malloc(n * sizeof(Point));
        if (points == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        // Fill the array with random points in the domain [0,1)x[0,1).
        for (int i = 0; i < n; i++) {
            points[i] = generateRandomPoint();
            // printf("Point: (%f, %f)\n", points[i].x, points[i].y);
        }

        // Execute both algorithms with same array NUMBER_REPS times.
        for (int rep = 1; rep < NUMBER_REPS + 1; rep++) {

            printf("Repetition number %d...\n", rep);
            double cpu_time_used_sl, cpu_time_used_rd;

            printf("- Finding closest pair with sweep-line...\n");
            clock_t start_time_sl, end_time_sl;
            start_time_sl = clock();
            Point *closestPair_sl = (Point *)malloc(2 * sizeof(Point));
            sweepline(points, n, closestPair_sl);
            end_time_sl = clock();
            cpu_time_used_sl = ((double)(end_time_sl - start_time_sl)) / CLOCKS_PER_SEC;
            printf("- Closest pair with sweep-line: (%.*lf, %.*lf) and (%.*lf, %.*lf)\n",
                   DBL_DIG, closestPair_sl[0].x, DBL_DIG, closestPair_sl[0].y,
                   DBL_DIG, closestPair_sl[1].x, DBL_DIG, closestPair_sl[1].y);
            free(closestPair_sl);

            printf("- Finding closest pair with randomized...\n");
            clock_t start_time_rd, end_time_rd;
            start_time_rd = clock();
            Point *closestPair_rd = (Point *)malloc(2 * sizeof(Point));
            sweepline(points, n, closestPair_rd);
            end_time_rd = clock();
            cpu_time_used_rd = ((double)(end_time_rd - start_time_rd)) / CLOCKS_PER_SEC;
            printf("- Closest pair with randomized: (%.*lf, %.*lf) and (%.*lf, %.*lf)\n",
                   DBL_DIG, closestPair_rd[0].x, DBL_DIG, closestPair_rd[0].y,
                   DBL_DIG, closestPair_rd[1].x, DBL_DIG, closestPair_rd[1].y);
            free(closestPair_rd);

            fprintf(results_file, "%d, %d, %lf, %lf\n", n, rep, cpu_time_used_sl, cpu_time_used_rd);
                
        }

        free(points);

    }

    fclose(results_file);
    return 0;
}
