#include <iostream>
#include <string>
#include "../lib/bazooka.hh"


void Bazooka::update(SDL_Renderer*& renderer){
  surface=IMG_Load("./images/bazooka.png");
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

bool Bazooka::update(Samy*& samy){
	if (abs(samy->getX()-_x) <= 20 && abs(samy->getY()-_y) <= 20)
	{
		samy->setWeapon(id);
		return true;
	}else{
		return false;
	}
}

Bazooka::Bazooka(double x, double y):Weapon(x,y){

}

Bazooka::~Bazooka(){
  std::cout << "~BazookaGone" << std::endl;
}

void Bazooka::update(SDL_Event event, SDL_Renderer*& renderer){
  
}