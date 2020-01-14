#include <iostream>
#include <string>
#include "../lib/terrain.hh"

Terrain::Terrain(const char* path_to_image){surface = IMG_Load(path_to_image);id = 1;}
Terrain::~Terrain(){std::cout << "~S" << std::endl;}
void Terrain::freeS(){SDL_FreeSurface(surface);}
SDL_Surface* Terrain::getSurface(){return surface;}
void Terrain::update(SDL_Event event, SDL_Renderer*& renderer){id += 1;}