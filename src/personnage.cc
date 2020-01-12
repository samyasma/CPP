#include <iostream>
#include <string>
#include "../lib/personnage.hh"

Personnage::Personnage(double x, double y, int vie, int stamina, const char* path_to_image):Shape(x, y){
	_vie = vie; 
	_stamina = stamina; 
	_vivant = true;
	surface = IMG_Load(path_to_image);
	destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
}


Personnage::Personnage(): Shape(){
  _vie=100;
  _stamina=100;
  _vivant=true;
}

void Personnage::freeS(){
	SDL_FreeSurface(surface);
}

SDL_Surface* Personnage::getSurface(){
	return surface;
}

bool Personnage::estVivant(){
	return _vivant;
}

SDL_Rect& Personnage::getdestR(){
	return destR;
}

Personnage::~Personnage(){
	//this->freeS(); ça marche pas
	SDL_DestroyTexture(player_im);
	std::cout << "~P" << std::endl;
}


void Personnage::setPicture(SDL_Renderer*& renderer){
	SDL_DestroyTexture(player_im);
	player_im = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

SDL_Texture* Personnage::getTexture(){
	return player_im;
}

bool Personnage::getJump(){
	return _jump;
}

int Personnage::getStamina(){
	return _stamina;
}

void Personnage::setLeft(){
	right = false;
}

int Personnage::getVie(){
	return _vie;
}

void Personnage::setRight(){
	right = true;
}

bool Personnage::getRight(){
	return right;
}