
typedef struct {
    double x, y;
} Point;

typedef struct Node {
    Point point;
    struct Node* next;
} Node;

typedef int (*IntFunction)(int);

double calculateDistance(Point p1, Point p2) {
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Calculates de d parameter used in the first part of the randomized algorithm.
// This d will be used for grid dxd squares.
float calculateParameterD(Point *points, int n) {

float current_min_d = 2; // 2 is greater than domain

    for(int i = 0; i<n; i++) {

        int index1 = rand(0,n);
        int index2 = rand(0,n);
        float p1 = points[index1];
        float p2 = points[index2];
        float d = calculateDistance(p1,p2);

        if(d<current_min_d) {
            current_min_d = d;    
        }

    }

    return d;
}

// The algorithm finds the closest pair of points and saves them in the array of size 2 closestPair.
void randomized(Point *points, int numPoints, Point *closestPair) {

    float d = calculateParameterD(points);

    // Create the hash table with the points, indexed by the hash of the index of the cell they belong to.
    Node* hashTable[m];
    createHashTable(points, hashTable, m, hashingFun, d);

    // Compare each point with surrounding quadrants’ points searching for minimum.
    comparePoints(points, hashTable, closestPair);

}

void createHashTable(Point* points, Node* hashTable, int m, IntFunction hashingFun, float d) {

}

void comparePoints(Point* points, array* hashTable, Point *closestPair) {

}

// Three hashing functions are used. The keys are the indices of the quadrants.
// For example, the space is divided as:
// 0  1  2  3  4  5 
// 6  7  8  9  10 11
// 12 13 14 15 16 17
// They return the index in the hash table using the index of its quadrant as a key.

int universalHashFun(int key) {

}

int fastestHashFun(int key) {

}

int mersenneHashFun(int key) {

}
