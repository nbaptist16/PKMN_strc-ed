#include <iostream>
#include <string>

#include "PokemonGym.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"

using namespace std;

PokemonGym::PokemonGym():Building('G', 1, Point2D()) 
//so the numbers here don't match up with G1 in model
{ //i'm gonna leave this how it is but change G1 to not so default
  //id_num = 1;
  //display_code = 'G';
  state = NOT_BEATEN;
  max_number_of_training_units = 10;
  num_training_units_remaining = max_number_of_training_units;
  stamina_cost_per_training_unit = 1;
  dollar_cost_per_training_unit = 1.0;
  experience_points_per_training_unit = 2;
  cout << "PokemonGym default constructed." << endl;
}

PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc):Building('G', in_id, in_loc)
{
  //id_num = in_id;
  max_number_of_training_units = max_training_units;
  stamina_cost_per_training_unit = stamina_cost;
  experience_points_per_training_unit = exp_points_per_unit;
  dollar_cost_per_training_unit = dollar_cost;
  //location = in_loc;
  
  //display_code = 'G';
  state = NOT_BEATEN;
  num_training_units_remaining = max_number_of_training_units;
  cout << "PokemonGym constructed." << endl;
}

double PokemonGym::GetDollarCost(unsigned int unit_qty)
{
  return dollar_cost_per_training_unit*unit_qty;
}

unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty)
{
  return stamina_cost_per_training_unit*unit_qty;
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining()
{
  return num_training_units_remaining;
}

bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina)
{
  if(budget >= dollar_cost_per_training_unit*unit_qty && stamina >= stamina_cost_per_training_unit*unit_qty)
    return true;
  else
    return false;
}

unsigned int PokemonGym::TrainPokemon(unsigned int training_units)
{
  if(num_training_units_remaining >= training_units)
    {
      num_training_units_remaining -= training_units;
      return experience_points_per_training_unit*training_units;
    }
  else
    {
      num_training_units_remaining = 0;
      return experience_points_per_training_unit*num_training_units_remaining; 
    }
}

int countz = 0;

bool PokemonGym::Update() //function shouldn't keep returning true if beaten(?)
{
  if(num_training_units_remaining == 0 && countz == 0) //&& state == NOT_BEATEN)
    {
      state = BEATEN;
      display_code = 'g';
      cout << display_code << id_num << " has been beaten" << endl;
      countz++;
      return true;
    }
  //else if(num_training_units_remaining > 0) 
  else if (num_training_units_remaining > 0)// && Update() == 0) //only executes if update returns false
    {
      countz = 0;
    }
    return false; //returns if haven't run out/ran out for the 2nd+ time
}

bool PokemonGym::IsBeaten()
{
  if(num_training_units_remaining == 0 && state == BEATEN)
    return true;
  else
    return false;
}

void PokemonGym::ShowStatus()
{
  cout << "Pokemon Gym Status: ";
  Building::ShowStatus();
  //cout << endl;
  cout << "Max number of training units: " << max_number_of_training_units << endl;
  cout << "Stamina cost per training unit: " << stamina_cost_per_training_unit << endl;
  cout << "Pokemon dollar cost per training unit: " << dollar_cost_per_training_unit << endl;
  cout << "Experience points per training unit: " << experience_points_per_training_unit << endl;
  cout << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;
  cout << endl;
}


PokemonGym::~PokemonGym()
{
    cout << "PokemonGym destructed." << endl;
}
