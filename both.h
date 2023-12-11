#ifndef BOTH_H
#define BOTH_H

// Struct to represent a point in [0,DOMAIN]x[0,DOMAIN].
typedef struct {
    double x, y;
} Point;

// Calculated the Euclidean distance between two points in R2.
double calculateDistance(Point p1, Point p2) {
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

#endif // BOTH_H