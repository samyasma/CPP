#include <iostream>
#include <string>
#include "../lib/bullet.hh"


Bullet::Bullet(double x, double y, int j):Shape(x+40,y-25)
{
	destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
	id_bullet = j;
}
Bullet::Bullet(double x, double y, int j, int i):Shape(x-40,y-25)
{
	destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
	right = false;
	id_bullet = j;}

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

void Bullet::freeS(){
	SDL_FreeSurface(surface);
}

SDL_Surface* Bullet::getSurface(){
	return surface;
}

SDL_Texture* Bullet::getTexture(){
	return bullet_im;
}

SDL_Rect& Bullet::getdestR(){
	return destR;
}
void Bullet::setTrue(){
	is_on_map = true;
}

void Bullet::setFalse(){
	is_on_map = false;
}

double Bullet::getX(){
	return _x;}

bool Bullet::getB(){
	return is_on_map;
}

bool Bullet::getRight(){return right;}
int Bullet::getId(){return id_bullet;}