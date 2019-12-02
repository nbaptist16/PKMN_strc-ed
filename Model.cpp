#include <iostream>
#include <string>

//#include "Point2D.h"
//#include "Vector2D.h"
//#include "GameObject.h"
//#include "PokemonCenter.h"
//#include "PokemonGym.h"
//#include "Pokemon.h"
#include "Model.h"
//#include "View.h"

using namespace std;

Model::Model()
{
  time = 0;
  /*
  for (int k = 0; k < 10; k++) //I spose I should initialize this stuff?
    {
      object_ptrs[k] = NULL;
      pokemon_ptrs[k] = NULL;
      center_ptrs[k] = NULL;
      gym_ptrs[k] = NULL;
    }
  */
  Point2D pk1(5,1);
  Point2D pk2(10,1);
  Point2D pc1(1,20);
  Point2D pc2(10,20);
  Point2D pg2(5,5);

  string pikachu = "Pikachu";
  string bulbasaur = "Bulbasaur"; //bless you for choosing bulbasaur, the greatest ever starter
  //pokemon_ptrs[0] = new Pokemon(1, pk1);
  //pokemon_ptrs[1] = new Pokemon(2, pk2);
  //center_ptrs[0] = new PokemonCenter(pc1, 1);


  pokemon_ptrs[0] = new Pokemon(pikachu, 1, 'P', 2, pk1);
  pokemon_ptrs[1] = new Pokemon(bulbasaur, 2, 'P', 1, pk2);
  center_ptrs[0] = new PokemonCenter(1, 1, 100, pc1);
  center_ptrs[1] = new PokemonCenter(2, 2, 200, pc2);
  gym_ptrs[0] = new PokemonGym(10, 1, 2.0, 3, 1, Point2D());
  gym_ptrs[1] = new PokemonGym(20, 5, 7.5, 8, 2, pg2);

  /*
  pokemon_ptrs[0] = new Pokemon(string("Pikachu"), 1, 'P', 2, Point2D (5, 1));
  pokemon_ptrs[1] = new Pokemon(string("Bulbasaur"), 2, 'P', 1, Point2D (10, 1));
  center_ptrs[0] = new PokemonCenter(1, 1, 100, Point2D (1, 20));
  center_ptrs[1] = new PokemonCenter(2, 2, 200, Point2D (10, 20));
  gym_ptrs[0] = new PokemonGym();
  gym_ptrs[1] = new PokemonGym(10, 1, 1.0, 2, 1, Point2D (5, 5));
  */
  object_ptrs[0] = pokemon_ptrs[0];
  object_ptrs[1] = pokemon_ptrs[1];
  object_ptrs[2] = center_ptrs[0];
  object_ptrs[3] = center_ptrs[1];
  object_ptrs[4] = gym_ptrs[0];
  object_ptrs[5] = gym_ptrs[1];
  
  /* shhhhhhucks
  GameObject*object_ptrs = new GameObject[10];
  Pokemon * pokemon_ptrs = new Pokemon[10];
  PokemonCenter * center_ptrs = new PokemonCenter[10];
  PokemonGym * gym_ptrs = new PokemongGym[10];
  */

  ///

  num_objects = 6;
  num_pokemon = 2;
  num_centers = 2;
  num_gyms = 2;
  
  cout << "Model default constructed" << endl;
}

Pokemon * Model::GetPokemonPtr(int id)
{
  if(id == 1 || id == 2)
    return pokemon_ptrs[id-1];
  return NULL;
}

PokemonCenter * Model::GetPokemonCenterPtr(int id)
{
  if(id == 1 || id == 2)
    return center_ptrs[id-1];
  return NULL;
}

PokemonGym * Model::GetPokemonGymPtr(int id)
{
  if(id == 1 || id == 2)
    return gym_ptrs[id-1];
  return NULL;
}

bool Model::Update()
{
  time++;
  bool tempStore = 0;
  for (int i = 0; i < 6; i++)
    {
      //object_ptrs[i]->Update();
      if (object_ptrs[i]->Update() == 1)// == 1
	tempStore = true;
      else///added
	tempStore = false;///added
    }

  if ((gym_ptrs[0]->IsBeaten()) && (gym_ptrs[1]->IsBeaten()))
    {
      cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
      exit(EXIT_SUCCESS);
    }
  else if ((pokemon_ptrs[0]->IsExhausted()) && (pokemon_ptrs[1]->IsExhausted()))
    {
      cout << "GAME OVER: You lose! All of your Pokemon are tired!" << endl;
      exit(EXIT_FAILURE); //some real post-midterm vibes (iykyk)
    }
  return tempStore;
}

void Model::Display(View& view)
{
  cout << "Time: " << time << endl;
  this->ShowStatus();//
  view.Clear();
  for (int i = 0; i < 6; i++)
    {
      if (object_ptrs[i])
	  view.Plot(object_ptrs[i]);
    }
  view.Draw();
}

void Model::ShowStatus()
{
  for (int j = 0; j < 6; j++)
    {
      if(object_ptrs[j])
	object_ptrs[j]->ShowStatus();
    }
}

Model::~Model()
{
  for(int i = 0; i < 6; i++)
    {
      if (object_ptrs[i])
	{
	  delete object_ptrs[i];
	}
    }
  cout << "Model destructed." << endl;
}
