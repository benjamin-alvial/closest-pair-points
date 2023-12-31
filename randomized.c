#include <math.h>
#include "both.h"

#define DOMAIN 1 // The points live in [0,DOMAIN]x[0,DOMAIN].
#define EPSILON 0.000000000000001

// Global variables used in hashing functions.
unsigned long long prime;
int primeExp;
unsigned long long a;
unsigned long long b;
int tableSize;
int tableSizeExp;

// https://stackoverflow.com/questions/28115724/getting-big-random-numbers-in-c-c
unsigned long long llrand() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

// Struct to represent a node in a linked list where
// points will be stored in the hash table.
typedef struct Node {
    Point point;
    struct Node* next;
} Node;

// For defining hash functions int->int.
typedef int (*IntFunction)(int);

// General algorithm
void randomized(Point *points, int numPoints, IntFunction hashingFun, Point *closestPair);

// Calculate the d parameter used in the randomized algorithm
float calculateParameterD(Point *points, int n);

// Create hash table from points
void createHashTable(Point* points, int numPoints, IntFunction hashingFun, float d, Node** hashTable, int tableSize);
void freeHashTable(Node** hashTable, int tableSize);
int getQuadrantKeyFromPoint(Point point, float d);
void insertInHash(Node** hashTable, int key, IntFunction hashingFun, Point point);

// Compare points in table
void compareEachWithNeighbors(Point* points, int numPoints, IntFunction hashingFun, float d, Node** hashTable, Point *closestPair);
void newMinD(float* MinD, Point* closestPair, Point point,int col,int row, Node** hashTable, int gridDim, IntFunction hashingFun);

// Three hashing functions are used
int universalHashFun(int key);
int fasterHashFun(int key);
int mersenneHashFun(int key);

// The algorithm finds the closest pair of points and saves them in the array of size 2 closestPair.
// It works by dividing the space in a grid of dxd quadrants,
// creating a hash table to store all the points with quadrant's indices as keys,
// and comparing each point to surrounding quadrants using this hash table.

// For example:
// The space is [0,DOMAIN]x[0,DOMAIN]
// It is divided in quadrants of size dxd.
// The resulting indexing for the quadrants could be
// 0  1  2  3 
// 4  5  6  7 
// 8  9  10 11
// 12 13 14 15
// Doing idx=hash(15) will access the hash table at idx, 
// where the linked list with all points in this quadrant is stored.
void randomized(Point *points, int numPoints, IntFunction hashingFun, Point *closestPair) {

    primeExp = 61;
    prime = (1ULL<<primeExp) - 1; // 2^primeExp-1
    a = (llrand() % (prime-1)) + 1;
    b = (llrand() % (prime-1));
    tableSizeExp = 27;
    tableSize = (1ULL<<tableSizeExp); // 2^tableSizeExp-1

    // Calculate the parameter for the size of the quadrants.
    float d = calculateParameterD(points, numPoints);

    // Create the hash table with the points, indexed by the hash of the index of the quadrant they belong to.
    struct Node** hashTable = (struct Node**)malloc(tableSize * sizeof(struct Node*));
    createHashTable(points, numPoints, hashingFun, d, hashTable, tableSize);
    
    // Compare each point with surrounding quadrants’ points, searching for minimum.
    compareEachWithNeighbors(points, numPoints, hashingFun, d, hashTable, closestPair);

    freeHashTable(hashTable, tableSize);
    free(hashTable);

}

// Calculates de d parameter used in the first part of the randomized algorithm.
// This d will be used for grid dxd cells.
// It is calculated by picking n times pairs of points and returning the minimum distance.
float calculateParameterD(Point *points, int n) {

    float current_min_d = DOMAIN + 1; // greater than domain
    for(int i = 0; i<n; i++) {

        int index1 = rand() % n;
        int index2 = rand() % n;
        Point p1 = points[index1];
        Point p2 = points[index2];
        float d = calculateDistance(p1,p2);

        if(d<current_min_d && d>EPSILON) {
            current_min_d = d;    
        }

    }

    return current_min_d;
}

// Creates a hash table with linked lists of points.
// The hash table is an array that contains pointers to Nodes (linked lists).
// idx (int) | nptr (Node*), where *nptr = Node(p1, Node(p2, Node(p3, ..., Node(pz, NULL))))
// For example:
// 0 | nptr0, where *nptr0 = Node((x1,x1), Node((x2,y2), NULL))
// 1 | nptr1, where *nptr1 = NULL
// 2 | nptr2, where *nptr2 = Node((x3,x3), NULL)
// 3 | nptr3, where *nptr3 = Node((x4,x4), Node((x5,y5), NULL))
// ...
// Receives the array of points (and its size) which will be stored.
// Receives the hash function used to find where to store a point.
// Receives the parameter d to find the quadrant a point belongs to.
// Receives the hash table (and its size) where the pointers will be stored.
void createHashTable(Point* points, int numPoints, IntFunction hashingFun, float d, Node** hashTable, int tableSize) {

    for(int i = 0; i<tableSize; i++) {
        hashTable[i] = NULL;
    }

    for(int i = 0; i<numPoints; i++) {
        Point point = points[i];
        int key = getQuadrantKeyFromPoint(point, d);
        insertInHash(hashTable, key, hashingFun, point);
    }

}

void freeHashTable(Node** hashTable, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Calculates the index of the quadrant a given point belongs to.
int getQuadrantKeyFromPoint(Point point, float d) {
    int gridDim = ceil(DOMAIN/d); // grid is of size gridDimxgridDim
    int col = floor(point.x/d); // floor because indexing starts at 0
    int row = (gridDim-1) - floor(point.y/d); // indexing is top to bottom
    int key = col + gridDim*row; // quadrant index
    return key;
}

// Inserts the given point in the given hashTable at the index calculated
// using the given key and hashingFun.
void insertInHash(Node** hashTable, int key, IntFunction hashingFun, Point point) {
    int index = hashingFun(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->point = point;

    newNode->next = hashTable[index]; // Insert at beginning of linked list.
    hashTable[index] = newNode; // Update hash table pointer.
}

/// Iterates over the array of points, finds their quadrant and its neighbors, 
// compares the current point to all others in these quadrants, updating minimum.
// Returns an array with 5 values 0,1 -> point 1 , 2,3 -> point 2 , 4 -> Minimum distance saved
void compareEachWithNeighbors(Point* points, int numPoints, IntFunction hashingFun, float d, Node** hashTable, Point *closestPair) {
    int gridDim = ceil(DOMAIN/d);
    float MinD = DOMAIN+1;
    int MaxCell = gridDim -1;
    for(int i = 0; i < numPoints; i++){
        Point point = points[i];;
        int col = floor(point.x/d); 
        int row = (gridDim-1) - floor(point.y/d); 
        int key = col + gridDim*row;

        // By construction, there is at least one point here (itself)
        Node *ActualNode = hashTable[hashingFun(key)];
        do {
            float candidateDistance = calculateDistance(point,ActualNode->point);
            if(candidateDistance < MinD && candidateDistance>EPSILON){
                MinD = candidateDistance;
                closestPair[0] = point;
                closestPair[1] = ActualNode->point;
            }
            ActualNode = ActualNode->next;
        } while(ActualNode !=NULL);

        if(col == 0){
            if(row == 0){
                // Upper-left quadrant
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim, hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
            }
            else if(row == MaxCell){
                // Lower-left quadrant
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim,hashingFun);
            }
            else{
                // Left-side inner quadrants
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
            }
        }

        else if(col == MaxCell){
            if(row == 0){
                // Upper-right quadrant
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
            }
            else if(row == MaxCell){
                // Lower-right quadrant
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
            }
            else{
                // Right-side inner quadrants
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
            }
        }

        else {
            if(row == 0){
                // Upper-side inner quadrants
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim,hashingFun);
            }
            else if(row == MaxCell){
                // Lower-side inner quadrants
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim,hashingFun);
            }
            else{
                // Inner quadrants with 8 neighbors
                newMinD(&MinD,closestPair,point,col-1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row-1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col+1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row+1,hashTable,gridDim,hashingFun);
                newMinD(&MinD,closestPair,point,col-1,row,hashTable,gridDim,hashingFun);
            }
        }
    }

    return;
}

void newMinD(float* MinD, Point* closestPair, Point point,int col,int row, Node** hashTable,int gridDim, IntFunction hashingFun) {
    int key = col + gridDim*row;
    Node *ActualNode = hashTable[hashingFun(key)];

    if(ActualNode != NULL) {
        do {
            float candidateDistance = calculateDistance(point,ActualNode->point);
            if(candidateDistance< *MinD && candidateDistance>EPSILON){
                *MinD = candidateDistance;
                closestPair[0] = point;
                closestPair[1] = ActualNode->point;
            }
            ActualNode = ActualNode->next;
        } while(ActualNode !=NULL);

    }
    
}

// Three hashing functions are used. The keys are the indices of the quadrants.
// For example, the space is divided as:
// 0  1  2  3 
// 4  5  6  7 
// 8  9  10 11
// 12 13 14 15
// A key is a quadrant index, for example, key=13.
// Doing idx=hash(13) will return where in the hash table this quadrant is stored.
int universalHashFun(int key) {
    return ((a*key+b) % prime) % tableSize;
}

int fasterHashFun(int key) {
    return (((a*key+b) & ((1ULL<<63)-1))) >> (63-tableSizeExp);
}

int mersenneHashFun(int key) {

    unsigned long long x = a*key+b;
    x = (x & ((1<<primeExp)-1)) + (x>>primeExp);

    if(x>=prime) {
        x = x-prime; // Lowest value with mod p
    }

    return x & ((1<<tableSizeExp)-1); // mod m
}
