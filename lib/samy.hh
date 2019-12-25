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
	void update(SDL_Event event);
	void update();
private:
	int id;
};

#endif