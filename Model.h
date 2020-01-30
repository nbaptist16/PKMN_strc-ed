#ifndef MODEL_H
#define MODEL_H
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"

#include "Rival.h"
#include "BattleArena.h"

#include <list>
#include <iterator>
#include "string.h"

class Model {
    
public:
    //simulation time
    int time;

/***
    GameObject * object_ptrs[10];
    int num_objects;
    Pokemon * pokemon_ptrs[10];
    int num_pokemon;
    PokemonCenter * center_ptrs[10];
    int num_centers;
    PokemonGym * gym_ptrs[10];
    int num_gyms;

    //added for rivals n arena
    Rival * rival_ptrs[10];
    int num_rivals;
    BattleArena * arena_ptrs[10];
    int num_arenas;
***/

    list <GameObject*> object_ptrs;
    list <GameObject*> active_ptrs;
    list <Pokemon*> pokemon_ptrs;
    list <PokemonCenter*> center_ptrs;
    list <PokemonGym*> gym_ptrs;
    list <BattleArena*> arena_ptrs;
    list <Rival*> rival_ptrs;

    
public:
    Model();
    ~Model();
    Pokemon* GetPokemonPtr(int id);
    PokemonCenter* GetPokemonCenterPtr(int id);
    PokemonGym* GetPokemonGymPtr(int id);
    
    //added
    BattleArena* GetArenaPtr(int id);
    Rival* GetRivalPtr(int id);

    bool Update();
    void Display(View &view);
    void ShowStatus();
};


#endif
