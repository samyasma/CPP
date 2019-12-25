#include <iostream>
#include <string>
#include "../lib/samy.hh"

const int MAX_HEIGHT = 270; // niveau max quand on saute
const int GROUND = 400; // niveu du sol

void Samy::update(SDL_Event event, SDL_Renderer*& renderer){
    if (event.type == SDL_KEYUP)
    {
        this->reset(renderer);
    }
	switch (event.key.keysym.sym)
    {
        case SDLK_LEFT:  _x-=5; break;
        case SDLK_RIGHT: _x+=5; break;
        case SDLK_UP: 
            if (!_jump)
            {
                this->jump(); 
            }
            break;
        case SDLK_SPACE: this->Attack(renderer); break;
        case SDLK_LSHIFT: this->ramasse(renderer);break;
        //case SDLK_DOWN:  _y+=5; break;
    }
    destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
    this->decrease();
}

void Samy::update(){
    if (_jump)
    {
        if (_y >=MAX_HEIGHT && _up)
        {
            _y-=5;
            if (_y < MAX_HEIGHT)
            {
                _up = false;
                _down = true;
            }
        }else if (_down)
        {
            _y+=5;
            if (_y >GROUND)
            {
                _down = false;
                _jump = false;
            }
        }
    }
    //destR.x = _x;
    destR.y = _y;
}

void Samy::decrease(){
    _stamina -= 0.05;
}

void Samy::ramasse(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/samy_f.png");
    this->setPicture(renderer);
}

void Samy::Attack(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/samy_p.png");
    this->setPicture(renderer);
}

void Samy::reset(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/samy.png");
    this->setPicture(renderer);
}