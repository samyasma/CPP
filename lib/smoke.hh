#ifndef SMOKE_HPP_
#define SMOKE_HPP_
#include <iostream>
#include <string>
#include "../lib/personnage.hh"
#include "../lib/bullet.hh"
class Smoke : public Personnage{
public:
	//Smoke();
	~Smoke(){std::cout << "~Sm" << std::endl;}
	Smoke():Personnage(300,400,50,50, "./images/smoke.png"){id += 1;}
	Smoke(double x, double y):Personnage(x,y,50,50, "./images/smoke.png"){id += 1;}
	void update(SDL_Event event, SDL_Renderer*& renderer){}
	void Attack(SDL_Renderer*& renderer){}
	void CheckCollsion(Bullet* b);
	void update();
private:
	int id;
};

#endif
