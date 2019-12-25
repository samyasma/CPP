#ifndef PERSONNAGE_HPP_
#define PERSONNAGE_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Personnage: public Shape{
  public :
  Personnage();
  Personnage(double x, double y, int vie, int stamina, const char* path_to_image):Shape(x, y){_vie = vie; _stamina = stamina; _vivant = true;surface = IMG_Load(path_to_image);}
  void Attack();
  void Defense();
  virtual ~Personnage();
  void update();
  void Jump();
  void DoDamage();
  void TakeDamage();
  void freeS(){SDL_FreeSurface(surface);}
  SDL_Surface* getSurface(){return surface;}
  protected:
    int _vie;
    int _stamina;
    bool _vivant;
    SDL_Surface* surface;
};

#endif