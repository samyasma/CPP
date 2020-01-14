#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <iostream>
#include <string>
#include "shape.hh"
#include "samy.hh"

class Weapon: public Shape{
  public :
  Weapon();
  Weapon(double x, double y);
  ~Weapon();
  virtual void update(SDL_Event event, SDL_Renderer*& renderer) = 0;
  virtual void update(SDL_Renderer*& renderer) = 0;
  virtual bool update(Samy*& samy) = 0;
  void freeS();
  SDL_Surface* getSurface();
  void setPicture(SDL_Renderer*& renderer);
  SDL_Texture* getTexture();
  SDL_Rect& getdestR();
  void setTrue();
  void setFalse();
  bool getB();
  bool getRight();
  void setLeft();
  void setRight();
protected:
  bool right = true;
  bool is_on_map = false;
  SDL_Rect destR;
  //SDL_Surface* surface;
  SDL_Texture* weapon_im = nullptr;
};

#endif