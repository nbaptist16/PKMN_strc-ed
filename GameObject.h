#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream> //
#include "Point2D.h" //
#include "Vector2D.h"

using namespace std;

class GameObject
{
protected:
  Point2D location;
  int id_num;
  char display_code;
  char state;

public:
  GameObject();
  GameObject(char in_code);
  GameObject(Point2D in_loc, int in_id, char in_code);
  Point2D GetLocation();
  int GetId();
  char GetState();
  virtual void ShowStatus(); //changed to virtual
  virtual ~GameObject();
  //char GetDisplayCode();

  //additional pure virtual functions for linking
  virtual bool Update() = 0;
  virtual bool ShouldBeVisible() = 0;

  void DrawSelf(char * ptr);
};



#endif
