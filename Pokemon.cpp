#include "Pokemon.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// TODO: Pick sane default starting values
Pokemon::Pokemon() : GameObject('P') {
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    speed = 1;
    this->name = "Pokemon";
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;
    this->speed = 5.0;

    //location, id, and code prooobably taken care of by GameObject

    //new protected members initialized in new constructor
    this->health = 20; //YOU AIN'T GETTING ME THIS TIME PUNK
    this->store_health = health;
    this->physical_damage = 5;
    this->magical_damage = 4;
    this->defense = 15;
    target = NULL;
    is_in_arena = false;
    current_arena = NULL;

    cout << "Pokemon constructed. " << endl;
}

Pokemon::Pokemon(string name, int id, char in_code, unsigned int speed, Point2D in_loc) : GameObject(in_loc, id, in_code) {
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    this->name = name;
    this->speed = speed;
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;

    //location, id, code taken care of by GameObject

    //new protected members initialized in new constructor
    this->health = 20; //YOU AIN'T GETTING ME THIS TIME PUNK
    this->store_health = health;
    this->physical_damage = 5;
    this->magical_damage = 4;
    this->defense = 15;
    target = NULL;
    is_in_arena = false;
    current_arena = NULL;

    cout << "Pokemon constructed. " << endl;
}

Pokemon::Pokemon(char in_code) : GameObject(in_code) {
    stamina = 20;
    pokemon_dollars = 0.0;
    current_center = NULL;
    current_gym = NULL;
    stamina_points_to_buy = 0;
    training_units_to_buy = 0;
    this->name = name;
    this->speed = speed;
    is_in_gym = false;
    is_in_center = false;
    experience_points = 0;

    //code taken care of by GameObject
    //location and id, well, probably so (we'll see)

    //new protected members initialized in new constructor
    this->health = 20; //YOU AIN'T GETTING ME THIS TIME PUNK
    this->store_health = health;
    this->physical_damage = 5;
    this->magical_damage = 4;
    this->defense = 15;
    target = NULL;
    is_in_arena = false;
    current_arena = NULL;

    cout << "Pokemon constructed. " << endl;
}

//added new constructor
Pokemon::Pokemon(string in_name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc):GameObject(in_loc, in_id, 'P') //switched order cuz the writing for this was badbadnotgood
{
  stamina = 20;
  pokemon_dollars = 0.0;
  current_center = NULL;
  current_gym = NULL;
  stamina_points_to_buy = 0;
  training_units_to_buy = 0;
  this->name = in_name; //THIS IS WHERE I WENT WRONG
  this->speed = speed; //I FLIPPIN KNOW IT
  is_in_gym = false;
  is_in_center = false;
  experience_points = 0;

  this->id_num = in_id; //added these here
  this->display_code = in_code;
  this->location = in_loc;

  //new protected members initialized in new constructor
  this->health = hp; //YOU AIN'T GETTING ME THIS TIME PUNK
  this->store_health = hp;
  this->physical_damage = phys_dmg;
  this->magical_damage = magic_dmg;
  this->defense = def;
  target = NULL;
  is_in_arena = false;
  current_arena = NULL;

  cout << "Pokemon constructed. " << endl;
}


Pokemon::~Pokemon() {
    cout << "Pokemon destructed. " << endl;
}

// PA4 code goes here....
// ok
bool Pokemon::IsAlive()
{
  if (state != FAINTED || this->health <= 0)
    return true;
  else
    return false;
}

void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense)
{
  double damage;
  //changed following from doubles to ints to use %
  int rando_min = 0.0;
  int rando_max = 10.0;
  int rando = (double)rand()/RAND_MAX;
  int outs = rando_min + rando*(rando_max - rando_min);
  if (outs%2 == 0)
    {
      damage = (100.0 - defense)/100 * physical_damage; //add this-> @ defense?
      this->health -= damage;
      cout << "Aiyaah! A physical attack, Master!" << endl;
    }
  else
    {
      damage = (100.0 - defense)/100 * magical_damage; //add this-> @ defense?
      this->health -= damage;
      cout << "Aiyaah! A special attack, Master!" << endl;
    }
}

void Pokemon::ReadyBattle(Rival *in_target)
{
  if (state == IN_ARENA && current_arena->IsAbleToFight(pokemon_dollars, stamina) && !current_arena->IsBeaten() && in_target->IsAlive())
    {
      this->target = in_target;
      this->state = BATTLE;
    }
  else
    {
      state = IN_ARENA;
    }
}

bool Pokemon::StartBattle()
{
  //if ((this->IsAlive()) && (this->target->IsAlive())) //while?
  if (this->health >= 0 && this->target->GetHealth() >= 0)
    { // error: CANNOT BE USED AS A FUNCTION

      //rival always hits first
      this->TakeHit(physical_damage, magical_damage, defense);
      target->TakeHit(physical_damage, magical_damage, defense);
      return true;

      /*
      this->TakeHit(double target->physical_damage, double target->magical_damage, double this->defense);
      target->TakeHit(double this->physical_damage, double this->magical_damage, double target->defense);
      */
    }
  else
    return false;
}


bool Pokemon::IsExhausted() {
    return stamina == 0;
}

// returns true if the simulation should be stopped
bool Pokemon::Update() {
    bool arrived = false;
    unsigned int stamina_received = 0;
    unsigned int stamina_cost = 0;
    double dollar_cost = 0;
    unsigned int num_training_units = 0;
    unsigned int experience_gain = 0;
    switch (state) {
        case STOPPED:
            return false;
        case MOVING:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = STOPPED;
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        case MOVING_TO_GYM:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
	    //added for arena
	  else if (is_in_arena) {
	    current_arena->RemoveOnePokemon();
	    is_in_arena = false;
	  }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_GYM;
                    is_in_gym = true;
                    current_gym->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        case MOVING_TO_CENTER:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
	    //added for arena
	  else if (is_in_arena) {
	    current_arena->RemoveOnePokemon();
	    is_in_arena = false;
	  }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_CENTER;
                    is_in_center = true;
                    current_center->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        case RECOVERING_STAMINA:
            dollar_cost = current_center->GetDollarCost(stamina_points_to_buy);
            pokemon_dollars -= dollar_cost;
            stamina += current_center->DistributeStamina(stamina_points_to_buy);
            cout << "** " << name << " recovered " << stamina_points_to_buy << " stamina point(s)! **" << endl;
            stamina_points_to_buy = 0;
            state = IN_CENTER;
            return true;
        case TRAINING_IN_GYM:
            stamina_cost = current_gym->GetStaminaCost(training_units_to_buy);
            dollar_cost = current_gym->GetDollarCost(training_units_to_buy);
            experience_gain = current_gym->TrainPokemon(training_units_to_buy);
            stamina -= stamina_cost;
            pokemon_dollars -= dollar_cost;
            experience_points += experience_gain;
            cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
            cout << "** " << name << " gained " << experience_gain << " experience points! **" << endl;
            training_units_to_buy = 0;
            state = IN_GYM;
            return true;
        case EXHAUSTED:
        case IN_GYM:
        case IN_CENTER:

	  //added cases here     supposed to fix above...?
        case FAINTED:
	  return false;
        case IN_ARENA:
	  //nahhh
        case MOVING_TO_ARENA:
	  if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
	  //added for arena
	  else if (is_in_arena) {
	    current_arena->RemoveOnePokemon();
	    is_in_arena = false;
	  }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_ARENA;
                    is_in_arena = true;
                    current_arena->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        case BATTLE:
	  stamina -= (current_arena->GetStaminaCost());
	  pokemon_dollars -= (current_arena->GetDollarCost());
	  StartBattle();/////
	  if (!StartBattle())//target->IsAlive() == 0)
	    {
	      this->health = store_health;
	      state = IN_ARENA;
	      target->IsAlive();
	    }
	  else
	    {
	      this->state = FAINTED;
	      target->IsAlive();
	    }	      
        default:
            return false;
    }
}

void Pokemon::StartMovingToCenter(PokemonCenter* center) {
    if (!IsExhausted()) {
        if (location == center->GetLocation()) {
            cout << display_code << GetId() << ": I am already at the Pokemon Center!" << endl;
        } else {
            if (is_in_center) {
                current_center->RemoveOnePokemon(); // handles corner case
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            state = MOVING_TO_CENTER;
            current_center = center;
            SetupDestination(center->GetLocation());
            cout << display_code << GetId() << ": On my way to center " << center->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am exhausted so I can't move to recover stamina..." << endl;
}

void Pokemon::StartMovingToGym(PokemonGym* gym) {
    if (!IsExhausted()) {
        if (location == gym->GetLocation()) {
            cout << display_code << GetId() << ": I am already at the Pokemon Gym!" << endl;
        } else {
            if (is_in_gym) {
                current_gym->RemoveOnePokemon(); // handles corner case
                is_in_gym = false;
            } else if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            state = MOVING_TO_GYM;
            current_gym = gym;
            SetupDestination(gym->GetLocation());
            cout << display_code << GetId() << ": On my way to gym " << gym->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am exhausted so I shouldn't be going to the gym.." << endl;
}

void Pokemon::StartTraining(unsigned int num_training_units) {
    unsigned int training_units_in_gym = 0;
    if (!IsExhausted()) {
        if (state == IN_GYM || state == TRAINING_IN_GYM) {
            if (current_gym->IsAbleToTrain(num_training_units,
                                           pokemon_dollars, stamina)) {
                if (!current_gym->IsBeaten()) {
                    training_units_in_gym = current_gym->GetNumTrainingUnitsRemaining();
                    training_units_to_buy = min(num_training_units, training_units_in_gym);
                    state = TRAINING_IN_GYM;
                    cout << display_code << GetId() << ": Started " << training_units_to_buy
                         << " training unit(s) at Pokemon Gym " << current_gym->GetId() << endl;
                } else
                    cout << display_code << GetId() << ": Cannot train! This Pokemon Gym is already beaten!"
                         << current_gym->GetId() << endl;
            } else
                cout << display_code << GetId() << ": Not enough stamina and/or money for training" << endl;
        } else
            cout << display_code << GetId() << ": I can only train in a Pokemon Gym!" << endl;
    } else
        cout << display_code << GetId() << ": I am exhausted so no more training for me.." << endl;
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) {
    unsigned int stamina_count_in_center = 0;
    if (state == IN_CENTER || state == RECOVERING_STAMINA) {
        if (IsExhausted())
            cout << display_code << GetId() << ": I barely made it to the Pokemon center!" << endl;
        if (current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars)) {
            if (current_center->HasStaminaPoints()) {
                stamina_count_in_center = current_center->GetNumStaminaPointsRemaining();
                state = RECOVERING_STAMINA;
                stamina_points_to_buy = min(num_stamina_points, stamina_count_in_center);
                cout << display_code << GetId() << ": Started recovering " << stamina_points_to_buy
                     << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
            } else
                cout << display_code << GetId()
                    << ": Cannot recover! No stamina points available in this Pokemon Center "
                     << current_center->GetId() << endl;
        } else
            cout << display_code << GetId() << ": Not enough money to recover stamina." << endl;
    } else
        cout << display_code << GetId() << ": I can only recover stamina at a Pokemon Center!" << endl;
}

void Pokemon::StartMoving(Point2D dest) {
    if (!IsExhausted()) {
        if (dest == this->GetLocation()) {
            cout << display_code << GetId() << ": I'm already there. see?" << endl;
        } else {
            state = MOVING;
            SetupDestination(dest);
            cout << display_code << GetId() << ": On my way." << endl;
        }
    } else {
        cout << display_code << GetId() << ": I am exhausted. I may move but you just cannot see me. " << endl;
    }
}

//added start moving to arena fn
void Pokemon::StartMovingToArena(BattleArena* arena)
{
  SetupDestination(arena->GetLocation());
  /////
  if (!IsExhausted() && IsAlive()) { //added IsAlive()
        if (location == arena->GetLocation()) {
            cout << display_code << GetId() << ": I am already at the Battle Arena!" << endl;
        } else {
            if (is_in_gym) {
                current_gym->RemoveOnePokemon(); // handles corner case
                is_in_gym = false;
            } else if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_arena) {
	        current_arena->RemoveOnePokemon();
		is_in_arena = false;
	    }
            state = MOVING_TO_ARENA;
            current_arena = arena;
            SetupDestination(arena->GetLocation());
            cout << display_code << GetId() << ": On my way to arena " << arena->GetId() << endl;
        }
    } else if (state == EXHAUSTED) {
        cout << display_code << GetId() << ": I am exhausted so I shouldn't be going to the gym.." << endl;
    } else if (state == FAINTED) {
        cout << this->display_code << this->id_num << ": (I have fainted.)" << endl;
}
}//

void Pokemon::SetupDestination(Point2D dest) {
    destination = dest;
    delta = (destination - location)*(speed / GetDistanceBetween(destination, location));
}

void Pokemon::Stop() {
    state = STOPPED;
    cout << display_code << GetId() << ": Stopping.." << endl;
}

bool Pokemon::UpdateLocation() {
    //check if within one step
    if (fabs((destination - location).x) <= fabs(delta.x) &&
        fabs((destination - location).y) <= fabs(delta.y)) {
        location = destination;
        cout << display_code << GetId() << ": I’m there!" << endl;
        return true;
    }
    else {
        location = location + delta;
        cout << display_code << GetId() << ": step..." << endl;
        return false;
    }
}

string Pokemon::GetName() {
    return name;
}

double GetRandomAmountOfPokemonDollars() {
    double f_min = 0.0;
    double f_max = 2.0;
    double f = (double)rand() / RAND_MAX;
    return f_min + f * (f_max - f_min);
}

void Pokemon::ShowStatus() {
    cout << name << " status: ";
    GameObject::ShowStatus();
    switch (state) {
        case STOPPED:
            cout << " stopped" << endl;
            break;
        case MOVING:
            cout << " moving at a speed of " << speed
                 << " to " << destination << " at each step of " << delta << endl;
            break;
        case MOVING_TO_CENTER:
            cout << " heading to Pokemon Center " << current_center->GetId()
                 << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case MOVING_TO_GYM:
            cout << " heading to Pokemon Gym " << current_gym->GetId()
                 << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case IN_GYM:
            cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
            break;
        case IN_CENTER:
            cout << " inside Pokemon Center " << current_center->GetId() << endl;
            break;
        case TRAINING_IN_GYM:
            cout << " training in Pokemon Gym " << current_gym->GetId() << endl;
        case RECOVERING_STAMINA:
            cout << " recovering stamina in Pokemon Center " << current_gym->GetId() << endl;
            break;
        case EXHAUSTED:
            cout << endl;
        default:
            break;
    }
    //  Print stats here
    cout << "\tStamina: " << stamina << endl;
    cout << "\tPokemon Dollars: " << pokemon_dollars << endl;
    cout << "\tExperience Points: " << experience_points << endl;
    
    //added the eggstra stouf
    cout << "\tHealth: " << health << endl;
    cout << "\tPhysical Damage: " << physical_damage << endl;
    cout << "\tMagical Damage: " << magical_damage << endl;
    cout << "\tDefense: " << defense << endl;
}

bool Pokemon::ShouldBeVisible() {
    return !IsExhausted();
}
