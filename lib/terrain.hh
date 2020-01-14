#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Terrain: public Shape{
public:
	Terrain();
	Terrain(const char* path_to_image);
	~Terrain();
	void freeS();
	SDL_Surface* getSurface();
	void update(SDL_Event event, SDL_Renderer*& renderer);
private:
	int id;
};

#endif