#ifndef BAZOOKA_HPP_
#define BAZOOKA_HPP_

#include <iostream>
#include <string>
#include "weapon.hh"

class Bazooka: public Weapon{
  public :
  Bazooka();
  Bazooka(double x, double y):Weapon(x,y){id+=1;}
  ~Bazooka(){std::cout << "~BazookaGone" << std::endl;}
  void update(SDL_Event event, SDL_Renderer*& renderer){}
  void update(SDL_Renderer*& renderer);
protected:
  int id;
};

#endif