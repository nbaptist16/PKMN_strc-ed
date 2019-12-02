#include <iostream>
#include <string>

#include "PokemonCenter.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"

using namespace std;

PokemonCenter::PokemonCenter():Building('C', 1, Point2D())
{
  //display_code = 'C';
  stamina_capacity = 100;
  num_stamina_points_remaining = stamina_capacity;
  dollar_cost_per_stamina_point = 5;
  state = STAMINA_POINTS_AVAILABLE;
  cout << "PokemonCenter default constructed." << endl;
}

PokemonCenter::PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_cap, Point2D in_loc):Building('C', in_id, in_loc)
{
  //id_num = in_id;
  //location = in_loc;
  dollar_cost_per_stamina_point = stamina_cost;
  stamina_capacity = stamina_cap;

  //display_code = 'C';
  num_stamina_points_remaining = stamina_capacity;
  state = STAMINA_POINTS_AVAILABLE;

  cout << "PokemonCenter constructed." << endl;
}

bool PokemonCenter::HasStaminaPoints()
{
  if (num_stamina_points_remaining > 0)
    return true;
  else
    return false;
}

unsigned int PokemonCenter::GetNumStaminaPointsRemaining()
{
  return num_stamina_points_remaining;
}

bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
{
  if (budget >= dollar_cost_per_stamina_point*stamina_points)
    return true;
  else
    return false;
}

double PokemonCenter::GetDollarCost(unsigned int stamina_points)
{
  return dollar_cost_per_stamina_point*stamina_points;
}

unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed)
{
  if (num_stamina_points_remaining >= points_needed)
    {
      num_stamina_points_remaining -= points_needed;
      return points_needed;
    }
  else
    {
      return num_stamina_points_remaining;
      num_stamina_points_remaining = 0;
    }
}

int counts = 0;

bool PokemonCenter::Update()
{
  if(num_stamina_points_remaining == 0 && counts == 0)// && state == STAMINA_POINTS_AVAILABLE)
    {
      state = NO_STAMINA_POINTS_AVAILABLE;
      display_code = 'c';
      cout << "PokemonCenter " << id_num << " has ran out of stamina points." << endl;
      counts++;
      return true;
    }
  else if (num_stamina_points_remaining > 0) // && Update() == 0) //only executes if update returns false
    {
      counts = 0;
    }
  return false; //if haven't run out/ran out for the 2nd+ time
}

void PokemonCenter::ShowStatus()
{
  cout << "Pokemon Center Status: ";
  Building::ShowStatus();
  //cout << endl;
  cout << "Pokemon dollar cost per stamina point : " << dollar_cost_per_stamina_point << endl;
  cout << "has " << num_stamina_points_remaining << " stamina point(s) remaining." << endl;
  cout << endl;
}


PokemonCenter::~PokemonCenter()
{
    cout << "Pokemon Center destructed." << endl;
}
