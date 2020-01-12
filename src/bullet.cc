#include <iostream>
#include <string>
#include "../lib/bullet.hh"


Bullet::~Bullet(){
	this->freeS();
	SDL_DestroyTexture(bullet_im);
	std::cout << "~B" << std::endl;
}

void Bullet::setPicture(SDL_Renderer*& renderer){
	SDL_DestroyTexture(bullet_im);
	bullet_im = SDL_CreateTextureFromSurface(renderer, surface);
}

void Bullet::update(SDL_Renderer*& renderer){
	if (id_bullet == 2)
	{
		surface=IMG_Load("./images/bullet3.png");
	}
	else if (id_bullet == 1)
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
