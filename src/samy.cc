#include <iostream>
#include <string>
#include "../lib/samy.hh"

const int MAX_HEIGHT = 270; // niveau max quand on saute
const int GROUND = 400; // niveu du sol

void Samy::update(SDL_Event event, SDL_Renderer*& renderer){
    if(_vivant){
        if (event.type == SDL_KEYUP)
        {
            this->reset(renderer);
        }
    	switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  _x-=8; this->setLeft();break;
            case SDLK_RIGHT: _x+=8; this->setRight();break;
            case SDLK_UP:
                if (!_jump)
                {
                    this->jump();
                }
                break;
            case SDLK_SPACE:
              this->Attack(renderer);
              break;
            case SDLK_LSHIFT: this->ramasse(renderer);break;
            //case SDLK_DOWN:  _y+=5; break;
        }
    }else{
        this->dead(renderer);
    }
    destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
}

void Samy::dead(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/samy_dead.png");
    this->setPicture(renderer);
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

void Samy::ramasse(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/samy_f.png");
    this->setPicture(renderer);
}

void Samy::Attack(SDL_Renderer*& renderer){
	if (id_weapon == 1)
	{
		if(this->getRight()){
	        surface = IMG_Load("./images/samy_bazooka.png");
	    }else{
	        surface = IMG_Load("./images/samy_bazookar.png");
	    }
	}else{
	    if(this->getRight()){
	        surface = IMG_Load("./images/samy_p.png");
	    }else{
	        surface = IMG_Load("./images/samy_pr.png");
	    }
	}
    //std::cout << "marche" << std::endl;
    Isfiring=true;
    this->setPicture(renderer);
}

void Samy::reset(SDL_Renderer*& renderer){
    if (this->getRight())
    {
        surface = IMG_Load("./images/samy.png");
    }else{
        surface = IMG_Load("./images/samyr.png");
    }
    this->setPicture(renderer);
}

void Samy::setWeapon(int i){
	id_weapon = i;
}

void Samy::decrease(){   
    if (_stamina > 0)
    {
        _stamina -= 0.2;
    }else{
        _vie -= 0.1;
    }
    if (_vie <= 0)
    {
        _vivant = false;
    }
}
