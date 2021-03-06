#include "BattleArena.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

BattleArena::BattleArena() : Building('A')//, in_id, point2d)
//BattleArena::BattleArena() : Building() : GameObject('A')//, in_id, point2d)
{
  pokemon_count = 0;
  max_num_rivals = 3;
  num_rivals_remaining = max_num_rivals;
  dollar_cost_per_fight = 4;
  stamina_cost_per_fight = 3;
  state = RIVALS_AVAILABLE;
  
  cout << "BattleArena default constructed." << endl;
}

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar_cost, int in_id, Point2D in_loc) : Building('A', in_id, in_loc) //changed in_id to id and point2d to loc (see Building.cpp)...or maybe not
{
  //id, code, location taken care of by Building

  pokemon_count = 0;
  max_num_rivals = 3;
  num_rivals_remaining = max_num_rivals;
  dollar_cost_per_fight = 4;
  stamina_cost_per_fight = 3;
  state = RIVALS_AVAILABLE;
  
  cout << "BattleArena constructed." << endl;
}

unsigned int BattleArena::GetNumRivalsRemaining()
{
  return num_rivals_remaining;
}

bool BattleArena::HasEnoughRivals()
{
  if (this->num_rivals_remaining >= 1)
    return true;
  else
    return false;
}

double BattleArena::GetDollarCost()
{
  return dollar_cost_per_fight;
}

unsigned int BattleArena::GetStaminaCost()
{
  return stamina_cost_per_fight;
}

bool BattleArena::IsAbleToFight(double budget, unsigned int stamina)
{
  return (budget >= dollar_cost_per_fight && stamina >= stamina_cost_per_fight);
}

bool BattleArena::Update()
{
  if (state == RIVALS_AVAILABLE && num_rivals_remaining == 0) 
    {
      state = NO_RIVALS_AVAILABLE;
      display_code = 'a';
      cout << display_code << GetId() << " has been beaten" << endl;
      return true;
    }
  return false;
}

bool BattleArena::IsBeaten()
{
  return num_rivals_remaining == 0;
}

void BattleArena::ShowStatus()
{
  cout << "Battle Arena Status: ";
  Building::ShowStatus();
  cout << "Max number of rivals: " << num_rivals_remaining << endl; //@399
  cout << "Stamina cost per fight: " << stamina_cost_per_fight << endl;
  cout << "Pokemon dollar cost per fight: " << dollar_cost_per_fight << endl;
  cout << num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
  //cout << "Experience points: " << __ << endl;
  
    /*
  0 pokemon are in this building
  Stamina cost per fight: 3
  Pokemon dollar cost per fight: 2.5
  3 rival(s) are remaining for this arena
  Experience Points: 0
    */
}

int BattleArena::GetId()
{
  return this->id_num;
}
