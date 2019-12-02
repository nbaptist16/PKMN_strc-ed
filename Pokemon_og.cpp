#include <iostream>
#include <string>

#include "Pokemon.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"

using namespace std;

Pokemon::Pokemon()
{
  speed = 5;
  cout << "Pokemon default constructed." << endl;
  current_center = NULL;
  current_gym = NULL;
}

Pokemon::Pokemon(char in_code)
{
  speed = 5;
  cout << "Pokemon constructed." << endl;
  state = STOPPED;
  display_code = in_code;
  current_center = NULL;
  current_gym = NULL;
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
{
  speed = in_speed;
  name = in_name;
  cout << "Pokemon constructed." << endl;
  current_center = NULL;
  current_gym = NULL;
}

void Pokemon::StartMoving(Point2D dest)
{
  SetupDestination(dest);
  if(location.x == destination.x && location.y == destination.y)
    {
      cout << display_code << id << ": I'm already there. See?" << endl;
    }
  else if (state == EXHAUSTED)
    {
      cout << display_code << id << ": I am exhausted. I may move but you cannot see me." << endl;
    }
  else
    {
      state = MOVING;
      cout << display_code << id << ": On my way." << endl;
    }
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
  SetupDestination(center->GetLocation());
  if (state == EXHAUSTED)
    {
      cout << display_code << id << ": I am exhausted so I can't move to recover stamina..." << endl;
    }
  else if ((location.x == center->GetLocation().x) && (location.y == center->GetLocation().y))
    {
      cout << display_code << id << ": I am already at the Pokemon Center!" << endl;
    }
  else
    {
      state = MOVING_TO_CENTER;
      cout << display_code << id << ": on my way to center " << center->GetId() << "." << endl;
    }
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
  SetupDestination(gym->GetLocation());
  if (state == EXHAUSTED)
    {
      cout << display_code << id << ": I am exhausted so I shouldn't be going to the gym..." << endl;
    }
  else if (location.x == gym->GetLocation().x && location.y == gym->GetLocation().y)
    {
      cout << display_code << id << ": I am already at the Pokemon Gym!" << endl;
    }
  else
    {
      state = MOVING_TO_GYM;
      cout << display_code << id << ": On my way to gym " << gym->GetId() << endl;
    }
}

void Pokemon::StartTraining (unsigned int num_training_units)
{
  if(IsExhausted() == 0 && location.x == current_gym->GetLocation().x && location.y == current_gym->GetLocation().y && pokemon_dollars >= GetDollarCost(unit_qty) && stamina >= GetStaminaCost(unit_qty) && current_gym->IsBeaten == false)
    {
      state = TRAINING_IN_GYM;
      if(current_gym->GetNumTrainingUnitsRemaining() <= num_training_units)
	training_units_to_buy = current_gym->GetNumTrainingUnitsRemaining();
      else
	training_units_to_buy = num_training_units;
      //cout << display_code << id << ": Started to train at Pokemon Gym " << current_gym->GetId() << " with " << current_gym->GetNumTrainingUnitsRemaining() << " training units" << endl;
      //I'M CONFUSED
      cout << display_code << id << ": Started to train at Pokemon Gym " << current_gym->GetId() << " with " << stamina_points_to_buy << " training units" << endl;
    }
  if(IsExhausted() == 1)
    cout << display_code << id << ": I am exhausted so no more training for me..." << endl;
  if((location.x != current_gym->GetLocation().x || location.y != current_gym->GetLocation().y) || (location.x != current_gym->GetLocation().x && location.y != current_gym->GetLocation().y))
    cout << display_code << id << ": I can only train in a Pokemon Gym!" << endl;
  if(pokemon_dollars >= current_gym->GetDollarCost(unit_qty) && stamina >= current_gym->GetStaminaCost(unit_qty))
    cout << display_code << id << ": Not enough stamina and/or money for training" << endl;
  if(current_gym->IsBeaten() == 1)
    cout << display_code << id << ": Cannot train! This Pokemon Gym is already beaten!" << endl;
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
  if(pokemon_dollars >= current_center->GetDollarCost(unit_qty))
    {
      if(current_center->GetNumStaminaPointsRemaining >= 1)
	{
	  if(location.x == current_center->GetLocation().x && location.y == current_center->GetLocation().y)
	    {
	      state = RECOVERING_STAMINA;
	      if(current_center->GetNumStaminaPointsRemaining() <= num_stamina_points)
		stamina_points_to_buy = current_center->GetNumStaminaPointsRemaining();
	      else
		stamina_points_to_buy = num_stamina_points;
	      cout << display_code << id << ": Started recovering " << stamina_points_to_buy << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
	    }
	  else
	    cout << display_code << id << ": I can only recover stamina at a Pokemon Center!" << endl;
	}
      else
	cout << display_code << id << ": Cannot recover! No stamina points remaining in this Pokemon Center" << endl;
    }
  else
    cout << display_code << id << ": Not enough money to recover stamina." << endl;
	
}

void Pokemon::Stop()
{
  state = STOPPED;
  cout << display_code << id << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted()
{
  if(stamina == 0)
    return true;
}

bool Pokemon::ShouldBeVisible()
{
  if(state != EXHAUSTED)
    return true;
}

void Pokemon::ShowStatus()
{
  cout << name << " status: ";
  GameObject::ShowStatus();
  if(state == STOPPED)
    {
      cout << " stopped" << endl;
    }
  else if(state == MOVING)
    {
      cout << " moving at a speed of " << speed << " to destination <" << location.x << ", " << location.y << "> at each step of " << delta << "." << endl;
    }
  else if(state == MOVING_TO_CENTER)
    {
      cout << " heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
    }
  else if(state == MOVING_TO_GYM)
    {
      cout << " heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
    }
  else if(state == IN_CENTER)
    {
      cout << " inside Pokemon Center " << current_center->GetId() << endl;
    }
  else if(state == IN_GYM)
    {
      cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
    }
  else if(state == TRAINING_IN_GYM)
    {
      cout << " training in Pokemon Gym " << current_gym->GetId() << endl;
    }
  else if(state == RECOVERING_STAMINA)
    {
      cout << " recovering stamina in Pokemon Center " << current_center->GetId() << endl;
    }
}

bool Pokemon::Update()
{
  if(state == STOPPED)
    {
      return false;
    }
  else if(state == MOVING)
    {
      UpdateLocation();
      if(GetDistanceBetween(location,destination) == 0)
	{
	  state = STOPPED;
	  return true;
	}
    }
  else if(state == MOVING_TO_CENTER)
    {
      UpdateLocation();
      if(GetDistanceBetween(location,destination) == 0)
	{
	  state = IN_CENTER;
	  return true;
	}
    }
  else if(state == MOVING_TO_GYM)
    {
      UpdateLocation();
      if(GetDistanceBetween(location,destination) == 0)//I FORGOT ABOUT THIS >:/
	{
	  state = IN_GYM;
	  return true;
	}
    }
  else if(state == IN_CENTER || state == IN_GYM)
    {
      return false;
    }
  else if(state == TRAINING_IN_GYM)
    {
      stamina = stamina - current_gym->GetStaminaCost(unit_qty);
      pokemon_dollars = pokemon_dollars - current_gym->GetDollarCost(unit_qty);
      experience_points = experience_points + current_gym->TrainPokemon(training_units); //(c)heck
      cout << "** " << name << " completed " << training_units_to_buy << " training unit(s) **" << endl;
      cout << "** " << name << " gained " << current_gym->TrainPokemon(training_units) << " experience point(s)! **" << endl;
      state = IN_GYM;
      return true;
    }
  else if(state == RECOVERING_STAMINA)
    {
      stamina = stamina + current_center->DistributeStamina(points_needed);
      pokemon_dollars = pokemon_dollars - current_center->GetDollarCost(unit_qty);
      cout << "** " << name << " recovered " << current_center->DistributeStamina(points_needed) << " stamina point(s)! **" << endl;
    }
  //stamina = stamina - (1*delta);
  stamina --;
  //pokemon_dollars = pokemon_dollars + (GetRandomAmountOfPokemonDollars()*delta);
  pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();
  cout << "Stamina: " << stamina << endl;
  cout << "Pokemon Dollars: " << pokemon_dollars << endl;
  cout << "Experience Points: " << experience_points << endl;
}

bool Pokemon::UpdateLocation()
{
  if(GetDistanceBetween(location,destination) == 0)
    cout << display_code << id << ": I'm there!" << endl;
  else
    cout << display_code << id << ": step..." << endl;
}

void Pokemon::SetupDestination(Point2D dest)
{
  delta = (dest - location)*(speed/GetDistanceBetween(dest,location));
  destination = dest;
}

double GetRandomAmountOfPokemonDollars()
{
  return (double)rand() % 2.0;
}

string Pokemon::GetName()
{
  return name;
}
