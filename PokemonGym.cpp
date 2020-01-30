#include <iostream>
#include "Building.h"
#include "PokemonGym.h"
using namespace std;

PokemonGym::PokemonGym(): Building('G', 0, Point2D(0.0, 0.0)) {
    state = NOT_BEATEN;
    max_number_of_training_units = 10;
    num_training_units_remaining = max_number_of_training_units;
    stamina_cost_per_training_unit = 1;
    dollar_cost_per_training_unit = 1.0;
    experience_points_per_training_unit = 2;
    cout << "PokemonGym default constructed. " << endl;
}

PokemonGym::PokemonGym(unsigned int max_training_units,
                       unsigned int stamina_cost, double dollar_cost,
                       unsigned int exp_points_per_training, int in_id,
                       Point2D point2d): Building('G', in_id, point2d) {
    state = NOT_BEATEN;
    max_number_of_training_units = max_training_units;
    num_training_units_remaining = max_training_units;
    stamina_cost_per_training_unit = stamina_cost;
    dollar_cost_per_training_unit = dollar_cost;
    experience_points_per_training_unit = exp_points_per_training;
    cout << "PokemonGym constructed. " << endl;
}

bool PokemonGym::Update() {
    if (state == NOT_BEATEN && num_training_units_remaining == 0) {
        state = BEATEN; // current_gym closes when you beat all trainers
        display_code = 'g';
        cout << display_code << GetId() << " has been beaten" << endl;
        return true;
    }
    return false;
}

void PokemonGym::ShowStatus() {
    cout << "Pokemon Gym Status: ";
    Building::ShowStatus();
    cout << "\tMax number of training units: " << max_number_of_training_units << endl;
    cout << "\tStamina cost per training unit: " << stamina_cost_per_training_unit << endl;
    cout << "\tPokemon dollar cost per training unit: " << dollar_cost_per_training_unit << endl;
    cout << "\tExperience points per training: " << experience_points_per_training_unit << endl;
    cout << "\t" << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;
}

PokemonGym::~PokemonGym() {
    cout << "PokemonGym destructed. " << endl;
}

double PokemonGym::GetDollarCost(unsigned int training_units) {
    return training_units * dollar_cost_per_training_unit;
}

unsigned int PokemonGym::GetStaminaCost(unsigned int training_units) {
    return training_units * stamina_cost_per_training_unit;
}

unsigned int PokemonGym::GetMaxAllowableTrainingUnits(double budget, unsigned int stamina) {
    // TODO: check for division by zero
    unsigned int cost_by_stamina = stamina / stamina_cost_per_training_unit;
    unsigned int cost_by_budget = (int)(budget / dollar_cost_per_training_unit);
    unsigned int allowable_units = min(cost_by_budget, cost_by_stamina);
    return allowable_units;
}


unsigned int PokemonGym::TrainPokemon(unsigned int training_units) {
    unsigned int exp_points = 0;
    if (num_training_units_remaining >= training_units) {
        exp_points = training_units * experience_points_per_training_unit;
        num_training_units_remaining -= training_units;
    } else {
        exp_points = num_training_units_remaining * experience_points_per_training_unit;
        num_training_units_remaining = 0;
    }
    return exp_points;
}

bool PokemonGym::HasEnoughTrainingUnits(unsigned int training_units) {
    return num_training_units_remaining >= training_units;
}

bool PokemonGym::IsAbleToTrain(unsigned int training_units,
        double budget, unsigned int stamina) {
    return GetMaxAllowableTrainingUnits(budget, stamina) >= training_units;
}

bool PokemonGym::IsBeaten() {
    return num_training_units_remaining == 0;
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining() {
    return num_training_units_remaining;
}




