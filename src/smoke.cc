#include "../lib/smoke.hh"

void Smoke::update(SDL_Event event, SDL_Renderer*& renderer){
	_x += 2;
	destR.w = 128;
	destR.h = 128;
	destR.x = _x;
	destR.y = _y;
	_stamina -= 0.5;
	_vivant= true;
}

void Smoke::CheckCollsion(Bullet* b) {
        if (abs(b->getX()-this->getX())<15)
						{
            this->setPosition(1000,1142);
						destR.w = 128;
						destR.h = 128;
						destR.x = _x;
						destR.y = _y;
					}
					_vivant=false;
			}
