#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"

#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"

#include "Pokemon.h"

#include "Model.h"
#include "GameCommand.h"

#include "View.h"

using namespace std;

int main()
{
  cout << "EC327: Introduction to Software Engineering" << endl;
  cout << "Fall 2019" << endl;
  cout << "Programming Assignment 3" << endl;

  cout << "                   _                              " << endl;
  cout << "       _ __   ___ | | _____ _ __ ___   ___  _ ___  " << endl;
  cout << "      | |_ \\ / _ \\| |/ / _ \\ |_ ` _ \\ / _ \\| |_  \\ " << endl;
  cout << "      | |_) | (_) |   <  __/ | | | | | (_) | | | |" << endl;
  cout << "      | .__/ \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|" << endl;
  cout << "      |_|                                         " << endl;
  /*
  cout << "                   _                              " << endl;
  cout << "       _ __   ___ | | _____ _ __ ___   ___  _ __  " << endl;
  cout << "      | |_ \ / _ \| |/ / _ \ |_ ` _ \ / _ \| |_ \ " << endl;
  cout << "      | |_) | (_) |   <  __/ | | | | | (_) | | | |" << endl;
  cout << "      | .__/ \___/|_|\_\___|_| |_| |_|\___/|_| |_|" << endl;
  cout << "      |_|                                         " << endl;
  */
  cout << "coded with <3 by your neighborhood stovetop rice cooker" << endl;
  cout << endl;

  Model model;
  View view;

  model.Display(view);

  char command;
  int in1, in2, in3;

  //int idno;
  //int x;
  //int y;
  cout << endl << "Please enter a command: ";
  //cin >> command >> in1 >> in2 >> in3; og, get rid of cin in switch
  cin >> command;

  //cin >> command >> idno >> x >> y; this one works for m
  //Point2D pt2d (x,y); for use with m
 
  while (command != 'q')
    {
      switch (command)
	{
	case 'm':
	  {
	    cin >> in1 >> in2 >> in3;
	    int idp = in1;
	    Point2D pt2d (in2,in3);
	    if (model.GetPokemonPtr(idp)) //from @Model.cpp
	      {
		DoMoveCommand(model, idp, pt2d);
		//cout << "Moving " << model.GetPokemonPtr(idp)->GetName() << " to " << pt2d << endl;
	      }
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 'g':
	  {
	    cin >> in1 >> in2;
	    int idp = in1;
	    int idg = in2;
	    if (model.GetPokemonPtr(idp) && model.GetPokemonGymPtr(idg))
	      DoMoveToGymCommand(model, idp, idg);
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 'c':
	  {
	    cin >> in1 >> in2;
	    int idp = in1;
	    int idc = in2;
	    if (model.GetPokemonPtr(idp) && model.GetPokemonCenterPtr(idc))
	      DoMoveToCenterCommand(model, idp, idc);
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 's':
	  {
	    cin >> in1;
	    int idp = in1;
	    if (model.GetPokemonPtr(idp))
	      DoStopCommand(model, idp);
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 'r':
	  {
	    cin >> in1 >> in2;
	    int idp = in1;
	    unsigned int pts = in2;
	    if (model.GetPokemonPtr(idp)) //can also check if stampts valid
	      DoRecoverInCenterCommand(model, idp, pts);
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 't':
	  {
	    cin >> in1 >> in2;
	    int idp = in1;
	    unsigned int pts = in2;
	    if (model.GetPokemonPtr(idp)) //can also check if traipts valid
	      DoTrainInGymCommand(model, idp, pts);
	    else
	      cout << "Error: Please enter a valid command!" << endl;
	    break;
	  }
	case 'v':
	  {
	    DoGoCommand(model, view);
	    //cout << "Advancing one tick." << endl;
	    break;
	  }
	case 'x':
	  {
	    DoRunCommand(model, view);
	    //cout << "Advancing one tick" << endl;
	    break;
	  }
	default:
	  {
	    cout << "Error: Please enter a valid command!" << endl;
	    cout << "Please." << endl;
	    cin >> command;
	  }
	}
      
      //cin >> command >> command >> x >> y; nope!
      //cin >> command >> in1 >> in2 >> in3;
      //Point2D pt2d (x,y); not anymore!
      cout << endl << "Please enter a command: ";
      cin >> command;
    }
  
  return 0;
}
