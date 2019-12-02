#ifndef POKEMONCENTER_H
#define POKEMONCENTER_H

#include "Building.h"
#include "GameObject.h"
#include "Point2D.h"

class PokemonCenter: public Building
{
 private:
  unsigned int stamina_capacity;
  unsigned int num_stamina_points_remaining;
  double dollar_cost_per_stamina_point;
 public:
  PokemonCenter();
  PokemonCenter(int in_id, double staminaa_cost, unsigned int stamina_cap, Point2D in_loc);
  bool HasStaminaPoints();
  unsigned int GetNumStaminaPointsRemaining();
  bool CanAffordStaminaPoints(unsigned int stamina_points, double budget);
  double GetDollarCost(unsigned int stamina_points);
  unsigned int DistributeStamina(unsigned int points_needed);
  bool Update();
  void ShowStatus();
  ~PokemonCenter();
};

//should this go here...?
enum PokemonCenterStates
  {
    STAMINA_POINTS_AVAILABLE = 0,
    NO_STAMINA_POINTS_AVAILABLE = 1
};

#endif
