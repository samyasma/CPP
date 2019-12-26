#include "../lib/smoke.hh"

void Smoke::update(){
	if(_vie > 0){
		if (this->getRight())
		{
			_x += 2;
		}else{
			_x -= 2;
		}

		if (this->getRight() && _x >= 750)
		{
			this->setLeft();
		}

		else if(!this->getRight() && _x <= 50){
			this->setRight();
		}
		destR.w = 128;
		destR.h = 128;
		destR.x = _x;
		destR.y = _y;
	}else{
		_vivant = false;
	}
}

void Smoke::Attack(SDL_Renderer*& renderer){
	if(this->getRight()){
        surface = IMG_Load("./images/smoke_f.png");
    }else{
        surface = IMG_Load("./images/smoke_fr.png");
    }
    this->setPicture(renderer);
}

void Smoke::update(Samy*& samy, SDL_Renderer*& renderer){
	if (abs(samy->getX()-this->getX()) < 20)
	{
		this->Attack(renderer);
		samy->decrease();
	}else{
		this->reset(renderer);
	}
}

void Smoke::reset(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/smoke.png");
    this->setPicture(renderer);
}

void Smoke::CheckCollsion(Bullet* b) {
        if (abs(b->getX()-this->getX())<15 && abs(b->getY()-this->getY())<50)
						{
            //this->setPosition(1000,1142);
						destR.w = 128;
						destR.h = 128;
						destR.x = _x;
						destR.y = _y;
						b->setFalse();
						this->_vie -= 20;
					}
					//_vivant=false;
			}
