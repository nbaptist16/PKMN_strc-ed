#ifndef BUILDING_H
#define BUILDING_H
#include "GameObject.h"

class Building : public GameObject {
public:
    Building();
    //added this one
    Building(char code);
    Building(char code, int id, Point2D in_loc);
    ~Building();
    void AddOnePokemon();
    void RemoveOnePokemon();
    void ShowStatus();
    bool ShouldBeVisible();
private:
    unsigned int pokemon_count;
};
#endif
