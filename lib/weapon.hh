#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <iostream>
#include <string>
#include "shape.hh"
#include "samy.hh"

class Weapon: public Shape{
  public :
  Weapon();
  Weapon(double x, double y):Shape(x,y){destR.w = 128;destR.h = 128;destR.x = _x;destR.y = _y;}
  ~Weapon(){std::cout << "~WeaponGone" << std::endl;}
  virtual void update(SDL_Event event, SDL_Renderer*& renderer) = 0;
  virtual void update(SDL_Renderer*& renderer) = 0;
  virtual bool update(Samy*& samy) = 0;
  void freeS(){SDL_FreeSurface(surface);}
  SDL_Surface* getSurface(){return surface;}
  void setPicture(SDL_Renderer*& renderer){weapon_im = SDL_CreateTextureFromSurface(renderer, surface);SDL_FreeSurface(surface);}
  SDL_Texture* getTexture(){return weapon_im;}
  SDL_Rect& getdestR(){return destR;}
  void setTrue(){is_on_map = true;}
  void setFalse(){is_on_map = false;}
  bool getB(){return is_on_map;}
  bool getRight(){return right;}
  void setLeft(){right = false;}
  void setRight(){right = true;}
protected:
  bool right = true;
  bool is_on_map = false;
  SDL_Rect destR;
  SDL_Surface* surface;
  SDL_Texture* weapon_im = nullptr;
};

#endif