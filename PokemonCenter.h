#ifndef POKEMON_CENTER_H
#define POKEMON_CENTER_H
#include "Building.h"

enum PokemonCenterStates {
    STAMINA_POINTS_AVAILABLE = 0,
    NO_STAMINA_POINTS_AVAILABLE = 1
};

class PokemonCenter: public Building {
public:
    PokemonCenter();
    PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_capacity, Point2D in_loc);
    ~PokemonCenter();
    unsigned int DistributeStamina(unsigned int points_needed=1);
    bool Update();
    void ShowStatus();
    double GetDollarCost(unsigned stamina_points);
    bool HasStaminaPoints();
    unsigned int GetNumStaminaPointsRemaining();
    bool CanAffordStaminaPoints(unsigned int stamina_points, double budget);
private:
    double dollar_cost_per_stamina_point;
    unsigned int stamina_capacity;
    unsigned int num_stamina_points_remaining;
};
#endif
