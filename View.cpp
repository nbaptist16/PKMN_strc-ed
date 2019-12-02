#include <iostream>
#include <string>

//#include "Point2D.h"
//#include "Vector2D.h"
//#include "GameObject.h"
//#include "PokemonCenter.h"
//#include "PokemonGym.h"
//#include "Pokemon.h"
//#include "Model.h"
//#include "GameCommand.h"
#include "View.h"

using namespace std;

View::View():origin(0,0)
{
  size = 11;
  scale = 2;
  //origin.x = 0;
  //origin.y = 0;
}

void View::Clear()
{
  for (int x = 0; x < size; x++)
    {
      for (int y = 0; y < size; y++)
	{
	  grid[x][y][0] = '.';
	  grid [x][y][1] = ' ';
	}
    }
}

void View::Plot(GameObject * ptr)
{
  int x = 0, y = 0;

  bool check = GetSubscripts(x, y, ptr->GetLocation());
  if (check == 0)
    {
      return; //no output for invalid input
    }
  else if (check == 1)
    {
      char marker[2];
      //DrawSelf(GameObject * ptr);
      ptr->DrawSelf(marker);
      if (grid[x][y][0] == '.')
	{
	  grid[x][y][0] = *marker;
	  grid[x][y][1] = *(marker + 1);
	}
      else
	{
	  grid[x][y][0] = '*';
	  grid[x][y][1] = ' ';
	}
    }
}

///

void View::Draw(){

  bool sizeOdd = size %2 !=0;

  for(int y = size - 1; y>-2; y--){

    if(y==-1){

      cout << "  ";

      for(int scaleX = 0; scaleX < static_cast<int>((size-1) *scale)+3; scaleX += static_cast<int>(scale * 2))

	if(scaleX < 10)

	  cout << scaleX << "   ";

        else

	  cout << scaleX << "  ";

      cout << endl;

      break;

    }

    if(sizeOdd && y%2==0){

      int scaler = static_cast<int>(y*scale);

      cout << scaler;

      if(scaler < 10)

	 cout << " ";

     }

    else if(!sizeOdd && y%2==1){

      int scaler = static_cast<int>(y*scale);

      cout << scaler;

      if(scaler < 10)

	cout << " ";

    }

      

    else 

      cout << "  ";

    for(int x = 0; x < size; x++){

      cout << grid[x][y][0];
  
      cout << grid[x][y][1];

    }

    cout << endl;

  }

}


/*
void View::Draw()
{
  
}
*/

//void View::DrawSelf >> in GameObject


bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
  out_x = static_cast<int>((location.x - origin.x)/scale);
  out_y = static_cast<int>((location.y - origin.y)/scale);

  if(out_x < size && out_y < size && out_x >= 0 && out_y >= 0) //>=0 ??
    {
      return true;
    }
  cout << "An object is outside the display" << endl;
  return false;
}
