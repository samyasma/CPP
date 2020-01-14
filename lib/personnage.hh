#ifndef PERSONNAGE_HPP_
#define PERSONNAGE_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Personnage: public Shape{
  public :
  Personnage();
  Personnage(double x, double y, int vie, int stamina, const char* path_to_image);//:Shape(x, y){_vie = vie; _stamina = stamina; _vivant = true;surface = IMG_Load(path_to_image);destR.w = 128;destR.h = 128;destR.x = _x;destR.y = _y;}
  virtual void Attack(SDL_Renderer*& renderer) = 0;
  void Defense();
  virtual ~Personnage();
  virtual void update(SDL_Event event, SDL_Renderer*& renderer) = 0;
  void freeS();
  SDL_Surface* getSurface();
  bool estVivant();
  SDL_Rect& getdestR();
  void jump();
  void setPicture(SDL_Renderer*& renderer);
  SDL_Texture* getTexture();
  bool getJump();
  int getStamina();
  int getVie();
  void setLeft();
  void setRight();
  bool getRight();
  protected:
    int _vie;
    int _stamina;
    bool _vivant;
    bool _jump = false;
    bool _up = false;
    bool _down = false;
    bool right = true;
    //SDL_Surface* surface;
    SDL_Rect destR, srcR;
    SDL_Texture* player_im = nullptr;
};

#endif
