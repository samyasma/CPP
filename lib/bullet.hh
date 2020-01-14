#ifndef BULLET_HPP_
#define BULLET_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Bullet: public Shape{
  public :
  Bullet();
  Bullet(double x, double y, int j);
  Bullet(double x, double y, int j, int i);
  ~Bullet();
  void update(SDL_Event event, SDL_Renderer*& renderer){}
  void update(SDL_Renderer*& renderer);
  void reset(SDL_Renderer*& renderer);
  void freeS();
  SDL_Surface* getSurface();
  void setPicture(SDL_Renderer*& renderer);
  SDL_Texture* getTexture();
  SDL_Rect& getdestR();
  void setTrue();
  void setFalse();
  double getX();
  bool getB();
  bool getRight();
  int getId();
protected:
  //int _damage;
  int id_bullet = 0; // 0 : par défaut, 1 : bazooka
  bool right = true;
  bool is_on_map = false;
  SDL_Rect destR;
  //SDL_Surface* surface;
  SDL_Texture* bullet_im = nullptr;
};

#endif
