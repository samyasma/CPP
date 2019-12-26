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
		//_stamina -= 0.0005;
		//_vivant= true;
	}else{
		_vivant = false;
	}
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
