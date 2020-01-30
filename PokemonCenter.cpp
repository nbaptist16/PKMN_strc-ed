#include <iostream>
#include "PokemonCenter.h"

using namespace std;

PokemonCenter::PokemonCenter(): Building('C', 0, Point2D(0.0, 0.0) ) {
    this->state = STAMINA_POINTS_AVAILABLE;
    this->stamina_capacity = 100;
    this->num_stamina_points_remaining = stamina_capacity;
    this->dollar_cost_per_stamina_point = 5;
    cout << "PokemonCenter default constructed. " << endl;
}


PokemonCenter::PokemonCenter(int in_id, double stamina_cost,
        unsigned int stamina_capacity, Point2D in_loc) : Building('C', in_id, in_loc) {
    this->stamina_capacity = stamina_capacity;
    this->num_stamina_points_remaining = stamina_capacity;
    this->dollar_cost_per_stamina_point = stamina_cost;
    this->state = STAMINA_POINTS_AVAILABLE;
    cout << "PokemonCenter constructed. " << endl;
}

bool PokemonCenter::Update() {
    if (num_stamina_points_remaining == 0 && state == STAMINA_POINTS_AVAILABLE) {
        state = NO_STAMINA_POINTS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter " << GetId() << " has ran out of stamina points." << endl;
        return true;
    }
    return false;
}

PokemonCenter::~PokemonCenter() {
    cout << "PokemonCenter destructed. " << endl;
}

unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed) {
    unsigned int stamina_points = 0;
    if (num_stamina_points_remaining >= points_needed) {
        stamina_points = points_needed;
        num_stamina_points_remaining -= points_needed;
    } else {
        stamina_points = num_stamina_points_remaining;
        num_stamina_points_remaining = 0;
    }
    return stamina_points;
}

void PokemonCenter::ShowStatus() {
    cout << "Pokemon Center Status: ";
    Building::ShowStatus();
    cout << "\tPokemon dollar cost per stamina point: " << dollar_cost_per_stamina_point << endl;
    cout << "\thas " << num_stamina_points_remaining << " stamina point(s) remaining" << endl;
}

bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget) {
    return budget >= GetDollarCost(stamina_points);
}

double PokemonCenter::GetDollarCost(unsigned stamina_points) {
    return stamina_points * dollar_cost_per_stamina_point;
}

bool PokemonCenter::HasStaminaPoints() {
    return num_stamina_points_remaining > 0;
}

unsigned int PokemonCenter::GetNumStaminaPointsRemaining() {
    return num_stamina_points_remaining;
}


