#ifndef POINT2D_H
#define POINT2D_H

#include <iostream> //
#include "Vector2D.h" //

using namespace std;

class Point2D
{
 public:
  double x;
  double y;
  Point2D();
  Point2D(double in_x, double in_y);

  friend ostream& operator << (ostream& out, Point2D p1);

};

double GetDistanceBetween(Point2D p1, Point2D p2);
ostream& operator << (ostream& out, Point2D p1);
Point2D operator + (Point2D p1, Vector2D v1);
Vector2D operator - (Point2D p1, Point2D p2);

#endif
