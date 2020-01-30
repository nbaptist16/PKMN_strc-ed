#ifndef VIEW_H
#define VIEW_H
#include "Point2D.h"
#include "GameObject.h"

const int VIEW_MAX_SIZE = 20;

class View {
public:
    View();
    void Clear();
    void Plot(GameObject * ptr);
    void Draw();
private:
    //current size of the grid to be displayed
    int size;
    //the distance represented by each cell of the grid
    double scale;
    //the coordinates of the lower left-hand corner of the grid
    Point2D origin;
    //an array to hold the characters that make up the display grid
    char grid[VIEW_MAX_SIZE][VIEW_MAX_SIZE][2];
    //calculates the column and row subscripts of the grid array that correspond to the supplied location
    bool GetSubscripts(int &out_x, int &out_y, Point2D location);
};

#endif
