#include <iostream>
#include <string>
#include "../lib/dragonball.hh"


void DragonBall::update(SDL_Renderer*& renderer){
  surface=IMG_Load("./images/dragonball.png");
  if (this->getRight())
  {
    _x += 2;
  }else{
    _x -= 2;
  }
  if (this->getRight() && _x >= 750)
  {
    this->setLeft();
  }
  else if (!this->getRight() && _x < 50)
  {
    this->setRight();
  }
  destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
  this->setPicture(renderer);
}

bool DragonBall::update(Samy*& samy){
	if (abs(samy->getX()-_x) <= 20 && abs(samy->getY()-_y) <= 20)
	{
		samy->setWeapon(id);
		return true;
	}else{
		return false;
	}
}