#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "divide-conquer.c"
#include "randomized.c"

// Different fixed-sized inputs, 
// to analyze dependence on input distribution
#define FIXED_INPUT_SIZE 5000000
#define FIXED_INPUT_REPS 101

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
    // This seed will allow for different d values in randomized in each repetition.
    srand(123);

    printf("============================================\n");
    printf("EXPERIMENT 3: DIFFERENT ARRAYS OF FIXED SIZE...\n");
    printf("============================================\n");

    // This file will be used to plot the performance data.
    FILE *results_file = fopen("results/performance_results_3.txt", "w");

    printf("--------------------------------------------\n");
    printf("Finding the closest pair from different %d points for %d repetitions...\n", FIXED_INPUT_SIZE, FIXED_INPUT_REPS);
    printf("--------------------------------------------\n");

    for (int rep = 1; rep < FIXED_INPUT_REPS + 1; rep++) {
        printf("Repetition number %d...\n", rep);
        printf("- Creating array...\n");

        Point *points = (Point *)malloc(FIXED_INPUT_SIZE * sizeof(Point));
        if (points == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        // Fill the array with random points in the domain [0,1)x[0,1).
        for (int i = 0; i < FIXED_INPUT_SIZE; i++) {
            points[i] = generateRandomPoint();
            // printf("Point: (%f, %f)\n", points[i].x, points[i].y);
        }

        //printf("- Finding closest pair with divide conquer...\n");
        clock_t start_time_dc = clock();
        Point *closestPair_dc = (Point *)malloc(2 * sizeof(Point));
        divideConquer(points, FIXED_INPUT_SIZE, closestPair_dc);
        clock_t end_time_dc = clock();
        double cpu_time_used_dc = ((double)(end_time_dc - start_time_dc)) / CLOCKS_PER_SEC;
        double closestDistance_dc =  calculateDistance(closestPair_dc[0],closestPair_dc[1]);
        printf("- Closest pair with divide conquer: (%.*lf, %.*lf) and (%.*lf, %.*lf) with distance %.*lf\n",
                DBL_DIG, closestPair_dc[0].x, DBL_DIG, closestPair_dc[0].y,
                DBL_DIG, closestPair_dc[1].x, DBL_DIG, closestPair_dc[1].y,
                DBL_DIG, closestDistance_dc);
        free(closestPair_dc);

        //printf("- Finding closest pair with randomized universal...\n");
        clock_t start_time_rdu = clock();
        Point *closestPair_rdu = (Point *)malloc(2 * sizeof(Point));
        randomized(points, FIXED_INPUT_SIZE, universalHashFun, closestPair_rdu);
        clock_t end_time_rdu = clock();
        double cpu_time_used_rdu = ((double)(end_time_rdu - start_time_rdu)) / CLOCKS_PER_SEC;
        double closestDistance_rdu =  calculateDistance(closestPair_rdu[0],closestPair_rdu[1]);
        printf("- Closest pair with randomized universal: (%.*lf, %.*lf) and (%.*lf, %.*lf) with distance %.*lf\n",
                DBL_DIG, closestPair_rdu[0].x, DBL_DIG, closestPair_rdu[0].y,
                DBL_DIG, closestPair_rdu[1].x, DBL_DIG, closestPair_rdu[1].y,
                DBL_DIG, closestDistance_rdu);
        free(closestPair_rdu);

        //printf("- Finding closest pair with randomized faster...\n");
        clock_t start_time_rdf = clock();
        Point *closestPair_rdf = (Point *)malloc(2 * sizeof(Point));
        randomized(points, FIXED_INPUT_SIZE, fasterHashFun, closestPair_rdf);
        clock_t end_time_rdf = clock();
        double cpu_time_used_rdf = ((double)(end_time_rdf - start_time_rdf)) / CLOCKS_PER_SEC;
        double closestDistance_rdf =  calculateDistance(closestPair_rdf[0],closestPair_rdf[1]);
        printf("- Closest pair with randomized faster: (%.*lf, %.*lf) and (%.*lf, %.*lf) with distance %.*lf\n",
                DBL_DIG, closestPair_rdf[0].x, DBL_DIG, closestPair_rdf[0].y,
                DBL_DIG, closestPair_rdf[1].x, DBL_DIG, closestPair_rdf[1].y,
                DBL_DIG, closestDistance_rdf);
        free(closestPair_rdf);

        //printf("- Finding closest pair with randomized mersenne...\n");
        clock_t start_time_rdm = clock();
        Point *closestPair_rdm = (Point *)malloc(2 * sizeof(Point));
        randomized(points, FIXED_INPUT_SIZE, mersenneHashFun, closestPair_rdm);
        clock_t end_time_rdm = clock();
        double cpu_time_used_rdm = ((double)(end_time_rdm - start_time_rdm)) / CLOCKS_PER_SEC;
        double closestDistance_rdm =  calculateDistance(closestPair_rdm[0],closestPair_rdm[1]);
        printf("- Closest pair with randomized mersenne: (%.*lf, %.*lf) and (%.*lf, %.*lf) with distance %.*lf\n",
                DBL_DIG, closestPair_rdm[0].x, DBL_DIG, closestPair_rdm[0].y,
                DBL_DIG, closestPair_rdm[1].x, DBL_DIG, closestPair_rdm[1].y,
                DBL_DIG, closestDistance_rdm);
        free(closestPair_rdm);

        free(points);
        fprintf(results_file, "%d, %lf, %lf, %lf, %lf\n", rep, cpu_time_used_dc, cpu_time_used_rdu, cpu_time_used_rdf, cpu_time_used_rdm);

    }

    fclose(results_file);
    return 0;
}
