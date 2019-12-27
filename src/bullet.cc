#include <iostream>
#include <string>
#include "../lib/bullet.hh"


void Bullet::update(SDL_Renderer*& renderer){
	if (id_bullet == 1)
	{
		surface=IMG_Load("./images/bullet2.png");
	}
	else{
  		surface=IMG_Load("./images/bullet.png");
	}
  	if(this->getRight()){
  		_x=_x+7;
  	}else{
  		_x=_x-7;
  	}
  	if (_x >= 800 || _x <= 0)
  	{
  		this->setFalse();
  	}
  	destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
  	this->setPicture(renderer);
}
