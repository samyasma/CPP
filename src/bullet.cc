#include <iostream>
#include <string>
#include "../lib/bullet.hh"


void Bullet::update(SDL_Renderer*& renderer){
  surface=IMG_Load("./images/bullet.png");
  _x=_x+5;
  destR.w = 128;
destR.h = 128;
destR.x = _x;
destR.y = _y;
  this->setPicture(renderer);
}
