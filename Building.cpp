#include <iostream>
#include <string>
#include <cmath>

#include "Building.h"
#include "Point2D.h"
#include "GameObject.h"

using namespace std;

Building::Building():GameObject('B')
{
  pokemon_count = 0;
  // GameObject.display_code = 'B';
  //display_code = 'B';
  cout << "Building default constructed." << endl;;
}

Building::Building(char in_code, int in_Id, Point2D in_loc):GameObject(in_loc, in_Id, in_code)
{
  /*
  GameObject.id_num = in_Id;
  GameObject.location = in_loc;
  GameObject.display_code = in_code;
  */
  id_num = in_Id;
  location = in_loc;
  display_code = in_code;
  
  pokemon_count = 0;
  cout << "Building constructed." << endl;
}

void Building::AddOnePokemon()
{
  pokemon_count++;
}

void Building::RemoveOnePokemon()
{
  if (pokemon_count > 0)
    pokemon_count--;
}

void Building::ShowStatus()
{
  cout << display_code << id_num << " located at " << location << endl;
  if (pokemon_count == 1)
    {
      cout << pokemon_count << " pokemon is in this building" << endl;
    }
  else
    {
      cout << pokemon_count << " pokemon are in this building" << endl;
    }
}

bool Building::ShouldBeVisible()
{
  return true;
}

Building::~Building()
{
    cout << "Building destructed." << endl;
}
