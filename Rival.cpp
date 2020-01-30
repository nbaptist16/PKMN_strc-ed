#include "Rival.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

Rival::Rival() : GameObject('R')//, id, in_loc)
{
  health = 20;
  physical_damage = 5;
  magical_damage = 4;
  defense = 15;
  is_in_arena = false;
  current_arena = NULL;

  //this->name = name;
  //this->speed = speed;
  state = ALIVE_RIVAL;
}

//Rival::Rival(string name, double speed, double hp, double phys_dmg,double magic_dmg, double def, int id, Point2D in_loc) : GameObject(in_loc, id, 'R')
  //og:GameObject('R', id, in_loc) reordered to match @GameObject.cpp
Rival::Rival(string name, double speed, double hp, double phys_dmg,double magic_dmg, double def, int id, BattleArena* arena) : GameObject(arena->GetLocation(), id, 'R')
{
  this->health = hp;
  this->physical_damage = phys_dmg;
  this->magical_damage = magic_dmg;
  this->defense = def;
  is_in_arena = false;
  current_arena = NULL;

  this->name = name;
  this->speed = speed;
  this->id_num = id;
}

void Rival::TakeHit(double physical_damage, double magical_damage, double defense)
{
  double damage;
  //changed following from double to int for use wiht %
  int rando_min = 0.0;
  int rando_max = 10.0;
  int rando = (int)rand()/RAND_MAX;
  int outs = rando_min + rando*(rando_max - rando_min);
  if (outs%2 == 0)
    {
      damage = (100.0 - defense)/100 * physical_damage; //add this-> @ defense?
      this->health -= damage;
      //cout << "Aiyaah! A physical attack, Master!" << endl;
      cout << "WOT U EGG [stabs him]" << endl;
    }
  else
    {
      damage = (100.0 - defense)/100 * magical_damage; //add this-> @ defense?
      this->health -= damage;
      cout << "ka mE hA ME HAAAAAAAAAAA" << endl;
    }
}

double Rival::get_phys_dmg()
{
  return physical_damage;
}

double Rival::get_magic_dmg()
{
  return magical_damage;
}

double Rival::get_defense()
{
  return defense;
}

double Rival::get_health()
{
  return health;
}

bool Rival::Update()
{
  if (state == ALIVE_RIVAL)
    return false;
  else if (state == FAINTED_RIVAL)
    return true;
}

void Rival::ShowStatus()
{
  cout << "Rival status: ";
  GameObject::ShowStatus();
  if (state == ALIVE_RIVAL)
    {
      cout << " alive 'n well" << endl;
      
      //added :O
      cout << "\tHealth: " << health << endl;
      cout << "\tPhysical Damage: " << physical_damage << endl;
      cout << "\tMagical Damage: " << magical_damage << endl;
      cout << "\tDefense: " << defense << endl;
    }
  else if (state == FAINTED_RIVAL)
    {
      cout << " *dunky voice* ded" << endl;
    }
}

bool Rival::IsAlive()
{
  if (this->health >0)
    {
      state = ALIVE_RIVAL;
      return true;
    }
  else
    {
      state = FAINTED_RIVAL;
      return false;
    }
}

bool Rival::ShouldBeVisible()
{
  if (this->state != FAINTED_RIVAL)
    return true;
  else
    return false;
}

int Rival::GetId()
{
  return this->id_num;
}

string Rival::GetName()
{
  return this->name;
}

double Rival::GetHealth()
{
  return this->health;
}
