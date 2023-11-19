// The points live in [0,DOMAIN]x[0,DOMAIN].
#define DOMAIN 1

// Struct to represent a point in [0,DOMAIN]x[0,DOMAIN].
typedef struct {
    double x, y;
} Point;

// Struct to represent a node in a linked list where
// points will be stored in the hash table.
typedef struct Node {
    Point point;
    struct Node* next;
} Node;

// For defining hash functions int->int.
typedef int (*IntFunction)(int);

// Calculated the Euclidean distance between two points in R2.
double calculateDistance(Point p1, Point p2) {
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Calculates de d parameter used in the first part of the randomized algorithm.
// This d will be used for grid dxd cells.
// It is calculated by picking n times pairs of points and returning the minimum distance.
float calculateParameterD(Point *points, int n) {

    float current_min_d = DOMAIN + 1; // greater than domain

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

    // Calculate the parameter for the size of the quadrants.
    float d = calculateParameterD(points);

    // Create the hash table with the points, indexed by the hash of the index of the quadrant they belong to.
    Node* hashTable[tableSize];
    createHashTable(points, numPoints, hashingFun, d, hashTable, tableSize);

    // Compare each point with surrounding quadrants’ points, searching for minimum.
    comparePoints(points, hashTable, closestPair);

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
void createHashTable(Point* points, int numPoints, IntFunction hashingFun, float d, Node* hashTable, int tableSize) {

}

// Iterates over the array of points, finds their quadrant and its neighbors, 
// compares the current point to all others in these quadrants, updating minimum.
void comparePoints(Point* points, array* hashTable, Point *closestPair) {

}

// Three hashing functions are used. The keys are the indices of the quadrants.
// For example, the space is divided as:
// 0  1  2  3 
// 4  5  6  7 
// 8  9  10 11
// 12 13 14 15
// A key is a quadrant index, for example, key=13.
// Doing idx=hash(15) will return where in the hash table this quadrant is stored.
int universalHashFun(int key) {

}

int fastestHashFun(int key) {

}

int mersenneHashFun(int key) {

}
