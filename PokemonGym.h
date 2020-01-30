#ifndef POKEMON_GYM_H
#define POKEMON_GYM_H
#include "Building.h"

enum PokemonGymStates {
    NOT_BEATEN = 0,
    BEATEN = 1
};

class PokemonGym: public Building {
public:
    PokemonGym();
    ~PokemonGym();
    PokemonGym(unsigned int max_training_units,
               unsigned int stamina_cost, double dollar_cost,
               unsigned int exp_points_per_training, int in_id,
               Point2D point2d);
    bool Update();
    void ShowStatus();
    double GetDollarCost(unsigned int training_units);
    unsigned int GetStaminaCost(unsigned int training_units);
    unsigned int TrainPokemon(unsigned int training_units);
    // NOTE: this function is not required in the assignment`
    // returns the max number of training units given 3 factors
    // budget: how much pokemon dollars pokemon has in possession
    // stamina: how much energy a pokemon has remaining
    // training_units_remaining: how many training units a pokemon has left to beat
    unsigned int GetMaxAllowableTrainingUnits(double budget, unsigned int stamina);
    bool IsAbleToTrain(unsigned int training_units,
                 double budget, unsigned int stamina);
    // NOTE: this function is not required in the assignment
    bool HasEnoughTrainingUnits(unsigned int training_units);
    unsigned int GetNumTrainingUnitsRemaining();
    bool IsBeaten();


private:
    unsigned int max_number_of_training_units;
    unsigned int num_training_units_remaining;
    unsigned int stamina_cost_per_training_unit;
    double dollar_cost_per_training_unit;
    unsigned int experience_points_per_training_unit;
};

#endif // POKEMON_GYM
