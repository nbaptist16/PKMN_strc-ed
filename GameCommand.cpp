//#include <iostream>
//#include <string>
//#include <cmath>

//#include "GameObject.h"
//#include "Point2D.h"
//#include "Vector2D.h"

//#include "Building.h"
//#include "PokemonCenter.h"
//#include "PokemonGym.h"

//#include "Pokemon.h"

//#include "Model.h"
#include "GameCommand.h"
//#include "View.h"

using namespace std;

void DoMoveCommand(Model & model, int pokemon_id, Point2D p1)
{
  // Pokemon * p = Model.GetPokemonPtr(id)
  // if (pokemon_id == *p || pokemon_id == *p)
  //if((pokemon_id == (model.object_ptrs[0])+1) || pokemon_id == (model.object_ptrs[1]+1))
  //if(pokemon_id == 1 || pokemon_id == 2)
  if(model.GetPokemonPtr(pokemon_id) != NULL)
  //if(model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id) <= 0)
    {
      //cout << "Moving " << Pokemon->GetName() << " to " << p1 << endl;
      cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName() << " to " << p1 << endl;
      model.GetPokemonPtr(pokemon_id)->StartMoving(p1);
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}


//so there are a lotta piazza posts about checking if stuff is valid, and @317 said just check if IDs are valid at a minimum (which I'm honestly at rn so...
//sorry, but not gonna really flesh out the error checking here yet


void DoMoveToCenterCommand(Model & model, int pokemon_id, int center_id)
{
  //if((pokemon_id == 1 || pokemon_id == 2) && (center_id == 1 || center_id ==2))
  //if(model.GetPokemonPtr(pokemon_id) && model.GetPokemonCenterPtr(center_id))
  if(model.GetPokemonPtr(pokemon_id) != NULL && model.GetPokemonCenterPtr(center_id) != NULL)
  //if((model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id)<= 0 || model.GetPokemonCenterPtr(center_id) >2 || model.GetPokemonCenterPtr(center_id) <= 0)
    {
      //cout << "Moving " << Pokemon->GetName() << " to center " << center_id << endl;
      cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName() << " to center " << center_id << endl;
      model.GetPokemonPtr(pokemon_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoMoveToGymCommand(Model & model, int pokemon_id, int gym_id)
{
  //if(model.GetPokemonPtr(pokemon_id) && model.GetPokemonGymPtr(gym_id))
  if(model.GetPokemonPtr(pokemon_id) != NULL && model.GetPokemonGymPtr(gym_id) != NULL)
    //if((model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id)<= 0 || model.GetPokemonGymPtr(gym_id) >2 || model.GetPokemonGymPtr(gym_id) <= 0)
    {
      //cout << "Moving " << Pokemon->GetName() << " to gym " << gym_id << endl;
      cout << "Moving " << model.GetPokemonPtr(pokemon_id)->GetName() << " to gym " << gym_id << endl;
      model.GetPokemonPtr(pokemon_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}
  
void DoStopCommand(Model & model, int pokemon_id)
{
  //if(model.GetPokemonPtr(pokemon_id))
  if(model.GetPokemonPtr(pokemon_id) != NULL)
    //if(model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id)<= 0)
    {
      //cout << "Stopping " << Pokemon->GetName() << " P " << pokemon_id << endl;
      cout << "Stopping " << model.GetPokemonPtr(pokemon_id)->GetName() << " P " << pokemon_id << endl;
      //P is the display_code, right?
      model.GetPokemonPtr(pokemon_id)->Stop();
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoTrainInGymCommand(Model & model, int pokemon_id, unsigned int training_units)
{
  //if(model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id)<= 0)
  if(model.GetPokemonPtr(pokemon_id) != NULL)
    {
      //cout << "Training " << Pokemon->GetName() << endl;
      cout << "Training " << model.GetPokemonPtr(pokemon_id)->GetName() << endl;
      model.GetPokemonPtr(pokemon_id)->StartTraining(training_units);
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
  //if(model.GetPokemonPtr(pokemon_id))
  if(model.GetPokemonPtr(pokemon_id) != NULL)
  //if(model.GetPokemonPtr(pokemon_id) >2 || model.GetPokemonPtr(pokemon_id)<= 0)
    {
      //cout << "Recovering " << Pokemon->GetName() << "'s stamina" <<  endl;
      cout << "Recovering " << model.GetPokemonPtr(pokemon_id)->GetName() << "'s stamina" << endl;
      model.GetPokemonPtr(pokemon_id)->StartRecoveringStamina(stamina_points);
    }
  else
    {
      cout << "Error: Please enter a valid command!" << endl;
    }
}


void DoGoCommand(Model& model, View& view)
{
  cout << "Advancing one tick." << endl;
  //model.Update();
  //model.Display(view);
  model.Update();
  model.Display(view);
}

void DoRunCommand(Model& model, View& view)
{
  // what the pdf says: cout << "Advancing one tick." << endl;
  // what Imma put:
  cout << "Advancing to the next event." << endl;
  int wwtw = 1; //"wibbley-wobbley" ringing any bells?
  while (wwtw <= 5 && (model.Update() == 0)) //st. john's perhaps
    {
      model.Display(view);
      wwtw++; //just google it
    }
  //model.Display(view); //i'm sorry
  
}

