#ifndef BULLET_HPP_
#define BULLET_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Bullet: public Shape{
  public :
  Bullet();
  Bullet(double x, double y, int j):Shape(x+40,y-25){destR.w = 128;destR.h = 128;destR.x = _x;destR.y = _y;id_bullet = j;}
  Bullet(double x, double y, int j, int i):Shape(x-40,y-25){destR.w = 128;destR.h = 128;destR.x = _x;destR.y = _y;right = false;id_bullet = j;}
  ~Bullet();
  void update(SDL_Event event, SDL_Renderer*& renderer){}
  void update(SDL_Renderer*& renderer);
  void reset(SDL_Renderer*& renderer);
  void freeS(){SDL_FreeSurface(surface);}
  SDL_Surface* getSurface(){return surface;}
  void setPicture(SDL_Renderer*& renderer){bullet_im = SDL_CreateTextureFromSurface(renderer, surface);}//SDL_FreeSurface(surface);}
  SDL_Texture* getTexture(){return bullet_im;}
  SDL_Rect& getdestR(){return destR;}
  void setTrue(){is_on_map = true;}
  void setFalse(){is_on_map = false;}
  double getX(){return _x;}
  bool getB(){return is_on_map;}
  bool getRight(){return right;}
  int getId(){return id_bullet;}
protected:
  //int _damage;
  int id_bullet = 0; // 0 : par défaut, 1 : bazooka
  bool right = true;
  bool is_on_map = false;
  SDL_Rect destR;
  SDL_Surface* surface;
  SDL_Texture* bullet_im = nullptr;
};

#endif
