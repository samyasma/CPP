#include <iostream>
#include <string>
#include "../lib/weapon.hh"

  Weapon::Weapon(double x, double y):Shape(x,y)
  { destR.w = 128;
  	destR.h = 128;
  	destR.x = _x;
  	destR.y = _y;}
  Weapon::~Weapon(){std::cout << "~WeaponGone" << std::endl;}
 
  void Weapon::freeS(){
  	SDL_FreeSurface(surface);}
  
  SDL_Surface* Weapon::getSurface(){
  	return surface;}
  
  void Weapon::setPicture(SDL_Renderer*& renderer){
  	weapon_im = SDL_CreateTextureFromSurface(renderer, surface);
  	SDL_FreeSurface(surface);
  }
  
  SDL_Texture* Weapon::getTexture(){return weapon_im;}
  
  SDL_Rect& Weapon::getdestR(){return destR;}
  
  void Weapon::setTrue(){is_on_map = true;}
  
  void Weapon::setFalse(){is_on_map = false;}
  
  bool Weapon::getB(){return is_on_map;}
  
  bool Weapon::getRight(){return right;}
  
  void Weapon::setLeft(){right = false;}
  
  void Weapon::setRight(){right = true;}