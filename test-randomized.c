#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

#include "randomized.c"

int trivialHashFun(int key) {
	return key;
}

int main() {

	int n = 5;
	float d = 0.4;
	
	Point *points = (Point *)malloc(n * sizeof(Point));
	points[0].x = 0.0;
	points[0].y = 0.8;
	points[1].x = 0.1;
	points[1].y = 0.1;
	points[2].x = 0.6;
	points[2].y = 0.9;
	points[3].x = 0.5;
	points[3].y = 0.3;
	points[4].x = 0.6;
	points[4].y = 0.2;

	printf("========== TEST 1: points in grid ==========\n");

    printf("Expected grid: \n");
    printf("- - - - - - - \n");
    printf("| 0 | 1 | 2 | \n");
	printf("- - - - - - - \n");
	printf("| 3 | 4 | 5 | \n");
	printf("- - - - - - - \n");
	printf("| 6 | 7 | 8 | \n");
	printf("- - - - - - - \n");

	printf("Expected results: \n");
	printf("Point (0.0,0.8) lands in quadrant of index 3\n");
	printf("Point (0.1,0.1) lands in quadrant of index 6\n");
	printf("Point (0.6,0.9) lands in quadrant of index 1\n");
	printf("Point (0.5,0.3) lands in quadrant of index 7\n");
	printf("Point (0.6,0.2) lands in quadrant of index 7\n");
	
	printf("Actual results: \n");
	for (int i = 0; i < n; i++) {
		Point point = points[i];
		int key = getQuadrantKeyFromPoint(point, d);
		printf("Point (%f, %f) lands in quadrant of index %d\n", point.x, point.y, key);
	}

	printf("========== TEST 2: create trivial hash table ==========\n");

	printf("The hashing function in this test is the identity.\n");

	printf("Expected results: \n");
	printf("Hash table at index 0 has NULL\n");
	printf("Hash table at index 1 has the point (0.6,0.9)\n");
	printf("Hash table at index 2 has NULL\n");
	printf("Hash table at index 3 has the point (0.0,0.8)\n");
	printf("Hash table at index 4 has NULL\n");
	printf("Hash table at index 5 has NULL\n");
	printf("Hash table at index 6 has the point (0.1,0.1)\n");
	printf("Hash table at index 7 has the points (0.5,0.3) and (0.6,0.2)\n");
	printf("Hash table at index 8 has NULL\n");

	printf("Actual results: \n");
	int tableSize = 20;
	struct Node** hashTable = (struct Node**)malloc(tableSize * sizeof(struct Node*));
    createHashTable(points, n, trivialHashFun, d, hashTable, tableSize);

	for (int i = 0; i < tableSize; i++) {
		printf("At index %d of the hash table we find...\n", i);
		Node* node = hashTable[i];

		while (node != NULL) {
			printf("- Point (%f, %f)\n", node->point.x, node->point.y);
			node = node->next;
		}
		
		printf("- NULL\n");
	}

    free(hashTable);
	free(points);
    return 0;
}