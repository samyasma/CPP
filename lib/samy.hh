#ifndef SAMY_HPP_
#define SAMY_HPP_

#include <iostream>
#include <string>
#include "../lib/personnage.hh"

class Samy : public Personnage{
public:
	//Smoke();
	~Samy(){std::cout << "~Sa" << std::endl;}
	Samy():Personnage(300,400,100,100, "./images/samy.png"){id += 1;}
	Samy(double x, double y):Personnage(x,y,100,100, "./images/samy.png"){id += 1;}
	void update(SDL_Event event, SDL_Renderer*& renderer);
	void update();
	void decrease(){_vie -= 20;}
	void Attack(SDL_Renderer*& renderer);
	void reset(SDL_Renderer*& renderer);
	void ramasse(SDL_Renderer*& renderer);
	bool getIsfiring(){return Isfiring;}
	void setIsfiring(bool b){Isfiring=b;}
	//void setLeft(){right = false;}
	//void setRight(){right = true;}
	//bool getRight(){return right;}
private:
	int id;
	bool Isfiring=false;
};

#endif
