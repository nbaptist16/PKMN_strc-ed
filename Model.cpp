#include "Model.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <cstdlib>
#include <iostream>
#include <string>

//added
using namespace std;
#include <list>
#include <iterator>

#include "Rival.h" //added these
#include "BattleArena.h"

Model::Model() {
    time = 0;

/***
    //Pikachu 1
    //name id code speed loc
    //pokemon_ptrs[0] = new Pokemon("Pikachu", 1, 'P', 2.0, Point2D(5, 1));
    pokemon_ptrs[0] = new Pokemon("Pikachu", 2.0, 20, 5, 4, 15, 1, 'P', Point2D(5, 1));
    object_ptrs[0] = pokemon_ptrs[0];
    //Pikachu 2     NO IT'S BULBASAUR
    //pokemon_ptrs[1] = new Pokemon("Bulbasaur", 2, 'P', 1.0, Point2D(10, 1));
    pokemon_ptrs[1] = new Pokemon("Bulbasaur", 1.0, 20, 5, 4, 15, 2, 'P', Point2D(10, 1));
    object_ptrs[1] = pokemon_ptrs[1];
    //PokemonCenter 1
    center_ptrs[0] = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    object_ptrs[2] = center_ptrs[0];
    //PokemonCenter 2
    center_ptrs[1] = new PokemonCenter(2, 2, 200,  Point2D(10, 20));
    object_ptrs[3] = center_ptrs[1];
    //PokemonGym
    gym_ptrs[0] = new PokemonGym(10, 1.0,
                                 2.0, 3, 1, Point2D(0, 0));
    object_ptrs[4] = gym_ptrs[0];
    gym_ptrs[1] = new PokemonGym(20, 5,
                                 7.5, 8, 2, Point2D(5, 5));
    object_ptrs[5] = gym_ptrs[1];

    //adding Arena here (?)
    arena_ptrs[0] = new BattleArena(3, 3, 4, 1, Point2D(15, 12));
    object_ptrs[6] = arena_ptrs[0];
    //gotta come first since rivals reference it...?
    

    //adding Rivals here
    rival_ptrs[0]  = new Rival("Dougie", 1, 1, 1, 1, 1, 1, arena_ptrs[0]->GetLocation());
    object_ptrs[7] = rival_ptrs[0];
    
    rival_ptrs[1] = new Rival("Mikey", 1, 1, 1, 1, 1, 2, arena_ptrs[0]->GetLocation());
    object_ptrs[8] = rival_ptrs[1];

    rival_ptrs[2] = new Rival("DenS'more", 1, 1, 1, 1, 1, 3, arena_ptrs[0]->GetLocation());
    object_ptrs[9] = rival_ptrs[2];


    num_objects = 10; //updated to account for 3 rivals and 1 arena
    num_pokemon = 2;
    num_centers = 2;
    num_gyms = 2;
    num_rivals = 3;
    num_arenas = 1;
    
***/

//with linkshtuf
//Pikachu 1
    Pokemon* p1 = new Pokemon("Pikachu", 2.0, 20, 5, 4, 15, 1, 'P', Point2D(5, 1));
    //Pikachu 2     NO IT'S BULBASAUR
    Pokemon* p2 = new Pokemon("Bulbasaur", 1.0, 20, 5, 4, 15, 2, 'P', Point2D(10, 1));
    //PokemonCenter 1
    PokemonCenter* c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    //PokemonCenter 2
    PokemonCenter* c2 = new PokemonCenter(2, 2, 200,  Point2D(10, 20));
    //PokemonGym
    PokemonGym* g1 = new PokemonGym(10, 1.0,
                                 2.0, 3, 1, Point2D(0, 0));
    PokemonGym* g2 = new PokemonGym(20, 5,
                                 7.5, 8, 2, Point2D(5, 5));

    //adding Arena here (?)
    BattleArena* a1 = new BattleArena(3, 3, 4, 1, Point2D(15, 12));
    //gotta come first since rivals reference it...?
    
    //adding Rivals here
    Rival* r1  = new Rival("Dougie", 1, 1, 1, 1, 1, 1, a1);
    
    Rival* r2 = new Rival("Mikey", 1, 1, 1, 1, 1, 2, a1);

    Rival* r3 = new Rival("DenS'more", 1, 1, 1, 1, 1, 3, a1);

       object_ptrs.push_back(p1);
       pokemon_ptrs.push_back(p1);

       object_ptrs.push_back(p2);
       pokemon_ptrs.push_back(p2);
       
       object_ptrs.push_back(c1);
       center_ptrs.push_back(c1);

       object_ptrs.push_back(c2);
       center_ptrs.push_back(c2);

       object_ptrs.push_back(g1);
       gym_ptrs.push_back(g1);

       object_ptrs.push_back(g2);
       gym_ptrs.push_back(g2);
    
       object_ptrs.push_back(a1);
       arena_ptrs.push_back(a1);

       object_ptrs.push_back(r1);
       rival_ptrs.push_back(r1);

       object_ptrs.push_back(r2);
       rival_ptrs.push_back(r2);

       object_ptrs.push_back(r3);
       rival_ptrs.push_back(r3);

       active_ptrs = object_ptrs;


    cout << "Model default constructed. " << endl;
}

Model::~Model() {
/***    
for (int i = 0; i < num_objects; i++) {
        delete object_ptrs[i];
    }
***/

list<GameObject*>::iterator iterator;
       
       for (iterator = object_ptrs.begin(); iterator != object_ptrs.end(); iterator++)
       {
           delete (*iterator);
       }
    cout << "Model destructed. " << endl;
}

Pokemon *Model::GetPokemonPtr(int id) {
/***    
for (int i = 0; i < num_pokemon; i++) {
        if (id == pokemon_ptrs[i]->GetId()) {
            return pokemon_ptrs[i];
        }
    }

    return 0;
***/

list<Pokemon*>::iterator iterator;
       iterator = pokemon_ptrs.begin();

       for (int i = 1; i < id; i++)
       {
           ++iterator;
       }

       return *iterator;
}

PokemonCenter *Model::GetPokemonCenterPtr(int id) {
  /***    
for (int i = 0; i < num_centers; i++) {
        if (id == center_ptrs[i]->GetId()) {
            return center_ptrs[i];
        }
    }
    return 0;
  ***/

list<PokemonCenter*>::iterator iterator;
       iterator = center_ptrs.begin();

       for (int i = 1; i < id; i++)
       {
           ++iterator;
       }

       return *iterator;
}

PokemonGym *Model::GetPokemonGymPtr(int id) {
  /*** 
   for (int i = 0; i < num_gyms; i++) {
        if (id == gym_ptrs[i]->GetId()) {
            return gym_ptrs[i];
        }
    }
    return 0;
  **/

list<PokemonGym*>::iterator iterator;
       iterator = gym_ptrs.begin();

       for (int i = 1; i < id; i++)
       {
           ++iterator;
       }

       return *iterator;
}

//added getptr functions for rival and arena
Rival *Model::GetRivalPtr(int id) {
  /***    
for (int i = 0; i < num_rivals; i++) {
        if (id == rival_ptrs[i]->GetId()) {
            return rival_ptrs[i];
        }
    }
    return 0;
  ***/

list<Rival*>::iterator iterator;
       iterator = rival_ptrs.begin();

       for (int i = 1; i < id; i++)
       {
           ++iterator;
       }

       return *iterator;
}

BattleArena *Model::GetArenaPtr(int id) {
  /***   
 for (int i = 0; i < num_arenas; i++) {
        if (id == arena_ptrs[i]->GetId()) {
            return arena_ptrs[i];
        }
    }
    return 0;
  ***/

list<BattleArena*>::iterator iterator;
       iterator = arena_ptrs.begin();

       for (int i = 1; i < id; i++)
       {
           ++iterator;
       }

       return *iterator;
}

bool Model::Update() {
    time++;
    int gyms_beaten = 0;
    int pokemon_exhausted = 0;
    int pokemon_fainted = 0;
    int arenas_beaten = 0;
    bool stats_return = false;

    /***
    //Calculating number of gyms beaten
    if (gyms_beaten != num_gyms) {
        for (int i = 0; i < num_gyms; i++) {
            if (gym_ptrs[i]->GetState() == BEATEN)
                gyms_beaten++;
        }
    }
    // Calculating number of pokemon that are tired
    if (pokemon_exhausted != num_pokemon) {
        for (int i = 0; i < num_pokemon; i++) {
            if (pokemon_ptrs[i]->IsExhausted())
                pokemon_exhausted++;
        }
    }
    bool event = false;
    // continue to update all
    if (gyms_beaten == num_gyms) {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }
    if (pokemon_exhausted == num_pokemon) {
        cout << "GAME OVER: You lose! All of your Pokemon are exhausted!" << endl;
        exit(EXIT_SUCCESS);
    }
    // update if winning condition is not met
    for (int i = 0; i < num_objects; i++) {
        bool temp = object_ptrs[i]->Update();
        if (temp) {
            event = temp;
        }
    }
    return event;
***/

list<GameObject*>::iterator iterator;

for (iterator = active_ptrs.begin(); iterator != active_ptrs.end(); iterator++)
  {
    if ((*iterator)->Update() == true)
            {
                stats_return = true;
            }
    if ((*iterator)->GetDisplayCode() == 'A')
            {
                if ((*iterator)->GetState() == NO_RIVALS_AVAILABLE)
                {
                    cout << "Battle Arena " << (*iterator)->GetId() << " has been removed" << endl;
                    iterator = active_ptrs.erase(iterator);
                }
            }
    if ((*iterator)->GetDisplayCode() == 'C' || (*iterator)->GetDisplayCode() == 'c')
            {
                if ((*iterator)->GetState() == NO_STAMINA_POINTS_AVAILABLE)
                {
                    cout << "Pokemon Center " << (*iterator)->GetId() << " has been removed" << endl;
                    iterator = active_ptrs.erase(iterator);
                }
            }
    if ((*iterator)->GetDisplayCode() == 'G' || (*iterator)->GetDisplayCode() == 'g')
            {
                if ((*iterator)->GetState() == BEATEN)
                {
                    cout << "Pokemon Gym " << (*iterator)->GetId() << " has been removed" << endl;
                    iterator = active_ptrs.erase(iterator);
                }
            }
    if ((*iterator)->GetDisplayCode() == 'P' || (*iterator)->GetDisplayCode() == 'p')
            {
                if ((*iterator)->GetState() == EXHAUSTED)
                {
                    cout << "Removed" << endl;
                    iterator = active_ptrs.erase((iterator));
                }
                if ((*iterator)->GetState() == FAINTED)
                {
                    cout << "Removed" << endl;
                    iterator = active_ptrs.erase((iterator));
                }

            }
    if ((*iterator)->GetDisplayCode() == 'R' || (*iterator)->GetDisplayCode() == 'r')
            {
                if ((*iterator)->GetState() == FAINTED_RIVAL)
                {
                    cout << "Removed" << endl;
                    iterator = active_ptrs.erase(iterator);
                }
            }
  }
cout << active_ptrs.size() << endl;

list<GameObject*>::iterator iterator1;

        for (iterator1 = object_ptrs.begin(); iterator1 != object_ptrs.end(); iterator1++)
        {
            if ((*iterator1)->GetDisplayCode() == 'P' || (*iterator1)->GetDisplayCode() == 'p')
            {
                if ((*iterator1)->GetState() == EXHAUSTED)
                {
                    pokemon_exhausted += 1;    
                }
                if ((*iterator1)->GetState() == FAINTED)
                {
                    pokemon_fainted += 1;    
                }
            }

            if ((*iterator1)->GetDisplayCode() == 'A')
            {
                if ((*iterator1)->GetState() == NO_RIVALS_AVAILABLE)
                {
                    arenas_beaten += 1;
                }
            }
        }

        
        if (arenas_beaten == arena_ptrs.size())
        {
            cout << "GAME OVER: You win! All Battle Arenas Beaten!" << endl;
            exit(EXIT_SUCCESS);
        }
        else if ( (pokemon_exhausted + pokemon_fainted) == pokemon_ptrs.size())
        {
            cout << "GAME OVER: You lose! All of your Pokemon are either tired or fainted!" << endl;
            exit(EXIT_FAILURE);
        }

        return stats_return;

}

void Model::Display(View &view) {
    view.Clear();
    /***
    for (int i = 0; i < num_objects; i++) {
        if (object_ptrs[i]->ShouldBeVisible()) {
            view.Plot(object_ptrs[i]);
        }
    }
    ***/

list<GameObject*>::iterator iterator;
       iterator = active_ptrs.begin();

       for (iterator = active_ptrs.begin(); iterator != active_ptrs.end(); iterator++)
       {
           view.Plot((*iterator));
       }
    view.Draw();
}

void Model::ShowStatus() {
  /***
    cout << "Time: " << time << endl;
    for (int i = 0; i < num_objects; i++) {
        object_ptrs[i]->ShowStatus();
    }
  ***/

list<GameObject*>::iterator iterator;
       iterator = object_ptrs.begin();

       
       for (int i = 0; i < object_ptrs.size(); i++ )
       {
           (*iterator)->ShowStatus();
           ++iterator;
       }
}
