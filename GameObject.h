#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Point2D.h"

class GameObject {
public:
    GameObject();
    GameObject(char in_code);
    GameObject(Point2D in_loc, int in_id, char in_code);
    virtual ~GameObject();
    Point2D GetLocation();
    int GetId();
    virtual void ShowStatus();
    void DrawSelf(char * ptr);
    char GetState();
    virtual bool Update() = 0;
    virtual bool ShouldBeVisible() = 0;

    //getters
    char GetDisplayCode();
    //string GetName();
protected:
    Point2D location;
    char display_code;
    char state;
    int id_num;
};
#endif
