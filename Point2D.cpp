#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

//default constructor
Point2D::Point2D() {
    x = 0.0;
    y = 0.0;
}

Point2D::Point2D(double inputx, double inputy) {
    x = inputx;
    y = inputy;
}

//calculates distance between two point2ds
double GetDistanceBetween(Point2D p1, Point2D p2) {
    return sqrt(pow(p1.x-p2.x,2.0)+pow(p1.y-p2.y,2.0));
}

//NOT Required in program document
bool operator == (Point2D p1, Point2D p2){
	if (p1.x == p2.x && p1.y == p2.y){
		return true;
	}
	return false;

}

//OLD ARTIFACT - DON'T USE
/*Point2D operator + (Point2D p1, Point2D p2) {
    return Point2D(p1.x + p2.x, p1.y + p2.y);
}*/

Vector2D operator - (Point2D p1, Point2D p2) {
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}

Point2D operator + (Point2D p1, Vector2D p2) {
    return Point2D(p1.x + p2.x, p1.y + p2.y);
}

ostream& operator << (ostream& out, Point2D p1) {
    out << "(" << p1.x << "," << p1.y << ")";
    return out;
}
