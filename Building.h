#ifndef BUILDING_H
#define BUILDING_H

#include "Point2D.h"
#include "GameObject.h"

class Building: public GameObject
{
 private:
  unsigned int pokemon_count;
  //char display_code;
  
 public:
  Building();
  Building(char in_code, int in_Id, Point2D in_loc);
  void AddOnePokemon();
  void RemoveOnePokemon();
  void ShowStatus();
  bool ShouldBeVisible();
  ~Building();
};

#endif
  
