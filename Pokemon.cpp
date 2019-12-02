#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "Pokemon.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"

using namespace std;

Pokemon::Pokemon():GameObject('P')
{
  speed = 5;
  stamina = 20;
  experience_points = 0;
  pokemon_dollars = 0;
  training_units_to_buy = 0;
  stamina_points_to_buy = 0;
  name = "Default Pokemon";
  destination = Point2D();
  state = STOPPED;
  delta = Vector2D(); 
 
  current_center = NULL;
  current_gym = NULL;

  is_in_gym = false;
  is_in_center = false;

  cout << "Pokemon default constructed." << endl;
}

Pokemon::Pokemon(char in_code):GameObject(in_code)
{
  speed = 5;
  is_in_gym = false;
  is_in_center = false;
  stamina = 20;
  experience_points = 0;
  pokemon_dollars = 0;
  training_units_to_buy = 0;
  stamina_points_to_buy = 0;
  name = "Default Pokemon";

  destination = Point2D();
  delta = Vector2D();
  state = STOPPED;
  //display_code = in_code;
  current_center = NULL;
  current_gym = NULL;

  cout << "Pokemon constructed." << endl;
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc):GameObject(in_loc, in_id, in_code)
{
  speed = in_speed;
  name = in_name;
  is_in_gym = false;
  is_in_center = false;
  stamina = 20;
  experience_points = 0;
  pokemon_dollars = 0.0;
  training_units_to_buy = 0;
  stamina_points_to_buy = 0;

  destination = Point2D();
  delta = Vector2D();
  state = STOPPED;
  current_center = NULL;
  current_gym = NULL;

  cout << "Pokemon constructed." << endl;
}

void Pokemon::StartMoving(Point2D dest)
{
  SetupDestination(dest);
  //if(location.x == destination.x && location.y == destination.y)

  if (state == IN_CENTER)
  {
      current_center->RemoveOnePokemon();
      current_center = NULL;
  }

  if (state == IN_GYM)
  {
      current_gym->RemoveOnePokemon();
      current_gym = NULL;
  }
  
  if (state == EXHAUSTED)
    {
      cout << display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
    }
  //if(GetDistanceBetween(location, destination) == 0) didn't prevent overshoot
  else if ((abs(this->location.x - dest.x)) <= abs(delta.x) && (abs(this->location.y - dest.y) <= abs(delta.y)))
    {
      cout << display_code << id_num << ": I'm already there. See?" << endl;
      this->location.x = dest.x;
      this->location.y = dest.y;
    }
  else
    {
      state = MOVING;
      cout << display_code << id_num << ": On my way." << endl;
    }
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
  SetupDestination(center->GetLocation());

  if (state == IN_CENTER)
  {
      current_center->RemoveOnePokemon();
      current_center = NULL;
  }
  if (state == IN_GYM)
  {
      current_gym->RemoveOnePokemon();
      current_gym = NULL;
  } 

  if (state == EXHAUSTED)
    {
      cout << display_code << id_num << ": I am exhausted so I can't move to recover stamina..." << endl;
    }
  else if ((location.x == center->GetLocation().x) && (location.y == center->GetLocation().y))
  //else if ((GetDistanceBetween(location, center->GetLocation()).x == 0) && (GetDistanceBetween(location, center->GetLocation()).y == 0))
    {
      cout << display_code << id_num << ": I am already at the Pokemon Center!" << endl;
    }
  else
    {
      state = MOVING_TO_CENTER;
      cout << display_code << id_num << ": on my way to center " << center->GetId() << "." << endl;
    }
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
  SetupDestination(gym->GetLocation());

  if (state == IN_CENTER)
  {
      current_center->RemoveOnePokemon();
      current_center = NULL;
  }
  if (state == IN_GYM)
  {
      current_gym->RemoveOnePokemon();
      current_gym = NULL;
  }

  if (state == EXHAUSTED)
    {
      cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the gym..." << endl;
    }
  else if (location.x == gym->GetLocation().x && location.y == gym->GetLocation().y)
  //else if (GetDistanceBetween(location, gym->GetLocation) == 0)
  //else if ((GetDistanceBetween(location, gym->GetLocation()).x == 0) && (GetDistanceBetween(location, gym->GetLocation()).y == 0))
    {
      cout << display_code << id_num << ": I am already at the Pokemon Gym!" << endl;
    }
  else
    {
      state = MOVING_TO_GYM;
      cout << display_code << id_num << ": On my way to gym " << gym->GetId() << endl;
    }
}

void Pokemon::StartTraining (unsigned int num_training_units)
{
  if (IsExhausted() == 1)
    cout << display_code << id_num << ": I am exhausted so no more training for me..." << endl;
  else if (is_in_gym == 0 || state != IN_GYM)
    cout << display_code << id_num << ": I can oly train in a Pokemon Gym!" << endl;
  else if ((current_gym->IsAbleToTrain(num_training_units, pokemon_dollars, stamina)) == 0)
    cout << display_code << id_num << ": Not enough stamina and/or money for training." << endl;
  else if (current_gym->IsBeaten() == 1)
    cout << display_code << id_num << ": Cannot train! This Pokemon Gym is already beaten!" << endl; 
  else
    {
      state = TRAINING_IN_GYM;
      if(num_training_units >= (current_gym->GetNumTrainingUnitsRemaining()))
	training_units_to_buy = current_gym->GetNumTrainingUnitsRemaining();
      else
	training_units_to_buy = num_training_units;
      cout << display_code << id_num << ": Started to train at Pokemon Gym" << current_gym->GetId() << " with " << training_units_to_buy << " training units" <<endl;

    }
}
 
void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
  if ((current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars)) == 0)
    cout << display_code << id_num << ": Not enough money to recover stamina." << endl;
  else if ((current_center->HasStaminaPoints()) == 0)
    cout << display_code << id_num << ":  Cannot recover! No stamina points remaining in this Pokemon Center." << endl;
  else if (is_in_center == 0)
    cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
  else
    {
      state = RECOVERING_STAMINA;
     
      if (num_stamina_points <= current_center->GetNumStaminaPointsRemaining())
	stamina_points_to_buy = num_stamina_points;
      else
	stamina_points_to_buy = current_center->GetNumStaminaPointsRemaining();
      cout << display_code << id_num << ": Started recovering " << stamina_points_to_buy << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
    }
}


void Pokemon::Stop()
{
  state = STOPPED;
  cout << display_code << id_num << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted()
{
  if(stamina == 0)
    return true;
  else
    return false;
}

bool Pokemon::ShouldBeVisible()
{
  if(state != EXHAUSTED)
    return true;
  else
    return false;
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
  else if(state == EXHAUSTED)
    {
      cout << " exhausted" << endl;
    }
  ///
  cout << "Stamina: " << stamina << endl;
  cout << "Pokemon Dollars: " << pokemon_dollars << endl;
  cout << "Experience Points: " << experience_points << endl;
  cout << endl;
}

bool Pokemon::Update() //corresponding to the enums # vals
{
  switch(state)
    {
    case STOPPED:
      {
	if (IsExhausted())
	  {
	    state = EXHAUSTED;
	    return true;
	  }
	else
	  return false;
	break;
      }
    case MOVING:
      {
	bool SUDOKU = UpdateLocation();
	if (SUDOKU && !IsExhausted())
	  {
	    state = STOPPED;
	    return true;
	  }
	else
	  {
	    if (IsExhausted())
	      {
		state = EXHAUSTED;
		return true;
	      }
	    else
	      {
		state = MOVING;
		return false;
	      }
	  }
	break;
      }
    case MOVING_TO_CENTER:
      {
	if (UpdateLocation() == 1 && IsExhausted() == false)
	  {
	    state = IN_CENTER;
	    current_center->AddOnePokemon();
	    return true;
	  }
	else if (UpdateLocation() == 0)
	  {
	    if (IsExhausted())
	      {
		state = EXHAUSTED;
		return true;
	      }
	    else
	      {
		state = MOVING_TO_CENTER;
		return false;
	      }
	  }
	break;
      }
    case MOVING_TO_GYM:
      {
	if (UpdateLocation() == 1 && IsExhausted() == false)
	  {
	    state = IN_GYM;
	    current_gym->AddOnePokemon();
	    return true;
	  }
	else if (UpdateLocation() == 0)
	  {
	    if (IsExhausted())
	      {
		state = EXHAUSTED;
		return true;
	      }
	    else
	      {
		state = MOVING_TO_GYM;
		return false;
	      }
	  }
	break;
      }
    case IN_CENTER:
      {
	if (IsExhausted())
         {
            state = EXHAUSTED;
            current_center->RemoveOnePokemon();
            return true;
         }
        else
         {
            return false;
         }
	break;
      }
    case IN_GYM:
      {
	if (IsExhausted())
	  {
	    state = EXHAUSTED;
	    current_gym->RemoveOnePokemon();
            return true;
          }
	else
	  {
	    return false;
	  }
	break;
      }
    case TRAINING_IN_GYM:
      {
	stamina -= current_gym->GetStaminaCost(training_units_to_buy);
	pokemon_dollars -= current_gym->GetDollarCost(training_units_to_buy);
	experience_points += current_gym->TrainPokemon(training_units_to_buy);
	cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
	cout << "** " << name << " gained " << current_gym->TrainPokemon(training_units_to_buy) << " experience point(s)! **" << endl;
	if (IsExhausted())
	  {
	    state = EXHAUSTED;
	    return true;
	  }
	else
	  {
	    state = IN_GYM;
	    return true;     
          }
	break;
      }
    case RECOVERING_STAMINA:
      {
	stamina += current_center->DistributeStamina(stamina_points_to_buy);
	pokemon_dollars -= current_center->GetDollarCost(stamina_points_to_buy);
	cout << "** " << name << " recovered " << current_center->DistributeStamina(stamina_points_to_buy) << " stamina point(s)! **" << endl;
	state = IN_CENTER;
	return true;
	break;
      }
    default:
      {
	return false;
	break;
      }
    }
}


  //stamina = stamina - (1*delta);
  //stamina --;
  //pokemon_dollars = pokemon_dollars + (GetRandomAmountOfPokemonDollars()*delta);
  //@piazza post 313:::pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();
 


bool Pokemon::UpdateLocation()
{
  if (IsExhausted() == true)
    {
      cout << display_code << id_num << ": is exhausted..." << endl;
      return false;
    }
  //else if(GetDistanceBetween(location,destination) == 0)
  else if (abs(this->location.x - this->destination.x) <= abs(this->delta.x) && abs(this->location.y - this->destination.y) <= abs(this->delta.y))
    {
      cout << display_code << id_num << ": I'm there!" << endl;
      this->location.x = destination.x;
      this->location.y = destination.y;
      return true;
    }
  else
    {
      cout << this->display_code << this->id_num << ": step..." << endl;
      this->location.x += delta.x;
      this->location.y += delta.y;
      stamina -= 1;
      pokemon_dollars += GetRandomAmountOfPokemonDollars();
      return false;
    }
}

void Pokemon::SetupDestination(Point2D dest)
{
  destination = dest;
  if (GetDistanceBetween(this->destination, this->location) != 0)
    {
      //delta = (dest - location)*(speed/GetDistanceBetween(dest,location));
      delta.x = (destination.x - location.x) * (speed / abs(GetDistanceBetween(destination, location)));
      delta.y = (destination.y - location.y) * (speed / abs(GetDistanceBetween(destination, location)));
    }
  else
    {
      delta.x = 0;
      delta.y = 0;
    }
}

double GetRandomAmountOfPokemonDollars()
{
  //return (double)rand() % 2.0;
  return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2.0));
}

string Pokemon::GetName()
{
  return name;
}

Pokemon::~Pokemon()
{
  cout << "Pokemon destructed." << endl;
}
