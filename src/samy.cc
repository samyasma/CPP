#include <iostream>
#include <string>
#include "../lib/samy.hh"
#include <SFML/Audio.hpp>

const int MAX_HEIGHT = 270; // niveau max quand on saute
const int GROUND = 400; // niveau du sol

Samy::~Samy(){
    std::cout << "~Sa" << std::endl;
}

Samy::Samy():Personnage(300,400,200,200, "./images/samy.png"){

}

Samy::Samy(double x, double y,unsigned int id):Personnage(x,y,200,200, "./images/samy.png"){
    _id=id;
}

bool Samy::getIsfiring(){
    return Isfiring;
}

void Samy::setIsfiring(bool b){
    Isfiring=b;
}

unsigned int Samy::getIdWeapon(){
    return id_weapon;
}

void Samy::update(SDL_Event event, SDL_Renderer*& renderer){
    if(_vivant){
        if (event.type == SDL_KEYUP)
        {
            this->reset(renderer);
        }
      if (_id==1){
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
        }
      else{
            switch(event.key.keysym.sym)
              {
            case SDLK_q:  _x-=8; this->setLeft();break;
            case SDLK_d: _x+=8; this->setRight();break;
            case SDLK_z:
                if (!_jump)
                {
                    this->jump();
                }
                break;
            case SDLK_c:
              this->Attack(renderer);
              break;
            case SDLK_v: this->ramasse(renderer);break;
          }
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
	if (id_weapon == 2)
	{
		if(this->getRight()){
	        surface = IMG_Load("./images/samy_sayen_ar.png");
	    }else{
	        surface = IMG_Load("./images/samy_sayen_a.png");
	    }
	}
	else if (id_weapon == 1)
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
	if (id_weapon == 2)
	{
		if (this->getRight())
	    {
	        surface = IMG_Load("./images/samy_sayen.png");
	    }else{
	        surface = IMG_Load("./images/samy_sayenr.png");
	    }
	}
	else{
	    if (this->getRight())
	    {
	        surface = IMG_Load("./images/samy.png");
	    }else{
	        surface = IMG_Load("./images/samyr.png");
	    }
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


void Samy::walk(SDL_Renderer*& renderer){
    id_walk += 0.5;
    if (right)
    {
        //std::cout << id_walk << std::endl;
        if(id_walk > 9){
            id_walk = 2;
        }
        std::string txt = "./images/younes" + std::to_string(int(floor(id_walk)))+".png";
        //std::string txt2 = ".png"
        const char *c = txt.c_str();
        surface = IMG_Load(c);
    }else{
        if(id_walk > 9){
            id_walk = 2;
        }
        std::string txt = "./images/younes" + std::to_string(int(floor(id_walk)))+"r.png";
        //std::string txt2 = ".png"
        const char *c = txt.c_str();
        surface = IMG_Load(c);
    }
    this->setPicture(renderer);
}
