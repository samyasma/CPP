#include "../lib/smoke.hh"

void Smoke::update(){
	if(_vie > 0){
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
	if (abs(samy->getX()-this->getX()) < 20 && abs(samy->getY()-this->getY())<30)
	{
		this->Attack(renderer);
		samy->decrease();
	}else{
		if (samy->getX() > this->getX())
		{
			_x += 3;
			//rand()%3+1;
			id_walk = double(id_walk+0.125);
			this->setRight();
		}else if(samy->getX() < this->getX()){
			_x -= 3;
			//rand()%3+1;
			id_walk = double(id_walk+0.125);
			this->setLeft();
		}
		// if (this->getRight())
		// {
		// 	_x += 2;
		// }else{
		// 	_x -= 2;
		// }

		// if (this->getRight() && _x >= 750)
		// {
		// 	this->setLeft();
		// }

		// else if(!this->getRight() && _x <= 50){
		// 	this->setRight();
		// }
		if(!a_recu){
			//this->reset(renderer);
			this->walk(renderer);
		}else{
			this->recoit(renderer);
			a_recu = false;
		}
	}

}

void Smoke::update(Samy*& samy,Samy*& younes, SDL_Renderer*& renderer){
if (samy->estVivant()==false || younes->estVivant()==false) {
	switch(samy->estVivant()) {
		case (false):
		this->update(younes,renderer);
		break;
	}
	switch(younes->estVivant()) {
		case (false):
		this->update(samy,renderer);
		break;
	}
}
else{
	//attack samy
	if (abs(samy->getX()-this->getX()) < 20 && abs(samy->getY()-this->getY())<30)
	{
		this->Attack(renderer);
		samy->decrease();
	}
	//attack younes
	if (abs(younes->getX()-this->getX()) < 20 && abs(younes->getY()-this->getY())<30 )
	{
		this->Attack(renderer);
		younes->decrease();
	}
	//strategy
	if (abs(samy->getX()-this->getX()) < abs(younes->getX()- this->getX())) {
				if (samy->getX() > this->getX())
				{
					_x += 3;
					id_walk = double(id_walk+0.125);
					this->setRight();
				}
				else if(samy->getX() < this->getX()){
					_x -= 3;
					//rand()%3+1;
					id_walk = double(id_walk+0.125);
					this->setLeft();
				}
				if(!a_recu){
					this->walk(renderer);
				}
				else{
					this->recoit(renderer);
					a_recu = false;
				}
			}
	if (abs(samy->getX()-this->getX()) > abs(younes->getX()- this->getX())) {
						if (younes->getX() > this->getX())
						{
							_x += 3;
							id_walk = double(id_walk+0.125);
							this->setRight();
						}
						else if(younes->getX() < this->getX()){
							_x -= 3;
							//rand()%3+1;
							id_walk = double(id_walk+0.125);
							this->setLeft();
						}
						if(!a_recu){
							this->walk(renderer);
						}
						else{
							this->recoit(renderer);
							a_recu = false;
						}
					}
}
}




void Smoke::walk(SDL_Renderer*& renderer){
	if (right)
	{
		//std::cout << id_walk << std::endl;
		if(id_walk > 9){
			id_walk = 2;
		}
		std::string txt = "./images/smoke" + std::to_string(int(floor(id_walk)))+".png";
		//std::string txt2 = ".png"
		const char *c = txt.c_str();
		surface = IMG_Load(c);
	}else{
		if(id_walk > 9){
			id_walk = 2;
		}
		std::string txt = "./images/smoke" + std::to_string(int(floor(id_walk)))+"r.png";
		//std::string txt2 = ".png"
		const char *c = txt.c_str();
		surface = IMG_Load(c);
	}
	this->setPicture(renderer);
}

void Smoke::reset(SDL_Renderer*& renderer){
    surface = IMG_Load("./images/smoke.png");
    this->setPicture(renderer);
}

void Smoke::recoit(SDL_Renderer*& renderer){
	surface = IMG_Load("./images/smoke_d.png");
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
						this->_vie -= 20 + 15*b->getId();
						a_recu = true;
					}
					//_vivant=false;
			}
