#ifndef DRAGONBALL_HPP_
#define DRAGONBALL_HPP_

#include <iostream>
#include <string>
#include "samy.hh"
#include "weapon.hh"

class DragonBall: public Weapon{
  public :
  DragonBall();
  DragonBall(double x, double y):Weapon(x,y){}
  ~DragonBall(){std::cout << "~DragonBallGone" << std::endl;}
  void update(SDL_Event event, SDL_Renderer*& renderer){}
  void update(SDL_Renderer*& renderer);
  bool update(Samy*& samy);
private:
  const int id = 2;
};

#endif