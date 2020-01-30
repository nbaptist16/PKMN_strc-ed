#ifndef VECTOR_2D_H
#define VECTOR_2D_H
#include <iostream>
using namespace std;

class Vector2D {
public:
    double x;
    double y;
    Vector2D();
    Vector2D(double, double);
};
Vector2D operator * (Vector2D, double);
Vector2D operator / (Vector2D, double);
ostream& operator<<(ostream&, Vector2D);
#endif
