#include "View.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Vector2D.h"
#include <iostream>

View::View() {
    size = 11;
    scale = 2;
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location) {
    Vector2D cv;
    cv = (location - origin) / scale;
    out_x = cv.x;
    out_y = cv.y;
    if (out_x >= 0 && out_x <= size - 1 && out_y >= 0 && out_y <= size - 1) {
        return true;
    }
    cout << "An object is outside the display" << endl;
    return false;
}

void View::Clear() {
    for (int i = 0; i < VIEW_MAX_SIZE; i++) {
        for (int j = 0; j < VIEW_MAX_SIZE; j++) {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject *ptr) {
    int ix, iy;
    bool valid;
    valid = GetSubscripts(ix, iy, ptr->GetLocation());
    if (valid && grid[ix][iy][0] == '.') {
        ptr->DrawSelf(grid[ix][iy]);
    }
    else if (valid) {
        grid[ix][iy][0] = '*';
        grid[ix][iy][1] = ' ';
    }
}

void View::Draw() {
    for (int j = size-1; j >= -1; j--) {
        for (int i = -1; i <= size-1; i++) {
            //grid axis
            if (i == -1 && j%2 == 0) {
                cout << j*2;
                if (j/5 == 0) {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0) {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0) {
                cout << i*2;
                if (i/5 == 0) {
                    cout << " ";
                }
                cout << "  ";
            }
            //draw objects
            if (i >= 0 && j >=0) {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}



