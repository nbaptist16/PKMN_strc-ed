#include <iostream>
#include <string>

#include "GameObject.h"
//#include "Point2D.h"
//#include "Vector2D.h"

using namespace std;

GameObject::GameObject()
{
  display_code = ' ';
}

 GameObject::GameObject(char in_code)
  {
    display_code = in_code;
    //id_num = '1';
    //state = '0';
    id_num = 1;
    state = 0;
    location = Point2D();
    cout << "GameObject constructed." << endl;
  }

  GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
  {
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    state = '0';
    cout << "GameObject constructed." << endl;
  }

  Point2D GameObject::GetLocation()
  {
    //return GameObject.location;
    return location;
  }

  int GameObject::GetId()
  {
    //return GameObject.id_num;
    return id_num;
  }

  char GameObject::GetState()
  {
    //return GameObject.state;
    return state;
  }
  
  void GameObject::ShowStatus()
  {
    /*
    cout << "<" << GameObject.display_code << ">";
    cout << "<" << GameObject.id_num << "> at ";
    cout << "<" << GameObject.location << ">";
    */
    cout << display_code << id_num << " at " << location << endl;
  }

GameObject::~GameObject()
{
  cout << "GameObject destructed." << endl;
}

void GameObject::DrawSelf(char * ptr)
{
  *ptr = display_code;
  //ptr[1] = id_num;
  *(ptr+1) = id_num + 48; //since just spitting out id_num didn't work :/
  // + 48 is dumb ascii code conversion ://////
  // sorta @http://www.cplusplus.com/forum/beginner/58429/

  /*
  if ((*ptr) == '.' && *(ptr+1) == ' ')
    {
      *ptr = this->display_code;
      *(ptr+1) = (char) (this->id_num + 48);
    }
  else
    {
      *ptr = '*';
      *(ptr+1) = ' ';
    }
  */
}
