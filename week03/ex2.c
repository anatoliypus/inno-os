#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Point {
    double x, y;
} Point;

double distance(Point* p1, Point* p2);
double area(Point* p1, Point* p2, Point* p3);

int main() {
    Point a, b, c;

    a.x = 2.5;
    a.y = 6;

    b.x = 1;
    b.y = 2.2;

    c.x = 10;
    c.y = 6;

    printf("Distance between A and B: %f\n", distance(&a, &b));
    printf("Area of triangle ABC: %f\n", area(&a, &b, &c));
    return 0;
}

double distance(Point* p1, Point* p2) {
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

double area(Point* p1, Point* p2, Point* p3) {
    return 0.5 * fabs(p1->x*p2->y - p2->x*p1->y +
                     p2->x*p3->y - p3->x*p2->y +
                     p3->x*p1->y - p1->x*p3->y);
}
