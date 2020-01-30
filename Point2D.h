#ifndef POINT2D
#define POINT2D
#include "Vector2D.h"
#include <iostream>
using namespace std;

class Point2D {
public:
    double x;
    double y;

    Point2D();

    Point2D(double, double);
};

double GetDistanceBetween(Point2D, Point2D);

bool operator == (Point2D, Point2D);

Vector2D operator - (Point2D, Point2D);

Point2D operator + (Point2D, Vector2D);

ostream& operator<<(ostream&, Point2D);

#endif
