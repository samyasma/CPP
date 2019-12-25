#include <iostream>
#include <string>
#include "../lib/samy.hh"

void Samy::update(SDL_Event event){
	switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:  _x-=5; break;
        case SDLK_RIGHT: _x+=5; break;
        case SDLK_UP:    _y-=5; break;
        case SDLK_DOWN:  _y+=5; break;
    }
    destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
	_stamina -= 0.5;
}