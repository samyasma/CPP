#ifndef PERSONNAGE_HPP_
#define PERSONNAGE_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Personnage: public Shape{
  public :
  Personnage();
  Personnage(double x, double y, int vie, int stamina, const char* path_to_image):Shape(x, y){_vie = vie; _stamina = stamina; _vivant = true;surface = IMG_Load(path_to_image);destR.w = 128;destR.h = 128;destR.x = _x;destR.y = _y;}
  void Attack();
  void Defense();
  virtual ~Personnage();
  virtual void update(SDL_Event event) = 0;
  void Jump();
  void DoDamage();
  void TakeDamage();
  void freeS(){SDL_FreeSurface(surface);}
  SDL_Surface* getSurface(){return surface;}
  bool estVivant(){return _vivant;}
  SDL_Rect& getdestR(){return destR;}
  void setPicture(SDL_Renderer*& renderer){player_im = SDL_CreateTextureFromSurface(renderer, surface);SDL_FreeSurface(surface);}
  SDL_Texture* getTexture(){return player_im;}
  protected:
    int _vie;
    int _stamina;
    bool _vivant;
    SDL_Surface* surface;
    SDL_Rect destR, srcR;
    SDL_Texture* player_im = nullptr;
};

#endif