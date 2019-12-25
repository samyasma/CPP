#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Terrain: public Shape{
public:
	Terrain();
	Terrain(const char* path_to_image){surface = IMG_Load(path_to_image);id = 1;}
	~Terrain(){std::cout << "~S" << std::endl;}
	void freeS(){SDL_FreeSurface(surface);}
	SDL_Surface* getSurface(){return surface;}
	void update(){id += 1;}
private:
	int id;
	SDL_Surface* surface;
};

#endif