#include <iostream>
#include <string>
#include "../lib/samy.hh"

void Samy::update(SDL_Event event){
	switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:  _x-=5; break;
        case SDLK_RIGHT: _x+=5; break;
        case SDLK_UP: this->jump(); break;
        //case SDLK_DOWN:  _y+=5; break;
    }
    destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
	_stamina -= 0.5;
}

void Samy::update(){
    if (_jump)
    {
        if (_y >=300 && _up)
        {
            _y-=5;
            if (_y < 300)
            {
                _up = false;
                _down = true;
            }
        }else if (_down)
        {
            _y+=5;
            if (_y >400)
            {
                _down = false;
                _jump = false;
            }
        }
    }
    destR.x = _x;
    destR.y = _y;
}