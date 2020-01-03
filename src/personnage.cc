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

// void Personnage::update(SDL_Event event){
// 	switch (event.key.keysym.sym)
//     {
//         case SDLK_LEFT:  _x-=5; break;
//         case SDLK_RIGHT: _x+=5; break;
//         case SDLK_UP:    _y-=5; break;
//         case SDLK_DOWN:  _y+=5; break;
//     }
//     destR.w = 128;
// 	destR.h = 128;
// 	destR.x = _x;
// 	destR.y = _y;
// 	_stamina -= 0.5;
// }

Personnage::~Personnage(){
	SDL_DestroyTexture(player_im);
	std::cout << "~P" << std::endl;
}


