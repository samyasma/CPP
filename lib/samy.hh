#ifndef SAMY_HPP_
#define SAMY_HPP_

#include <iostream>
#include <string>
#include "../lib/personnage.hh"

class Samy : public Personnage{
public:
	//Smoke();
	~Samy(){std::cout << "~Sa" << std::endl;}
	Samy():Personnage(300,400,200,200, "./images/samy.png"){}
	Samy(double x, double y):Personnage(x,y,200,200, "./images/samy.png"){}
	void update(SDL_Event event, SDL_Renderer*& renderer);
	void update();
	void decrease();
	void Attack(SDL_Renderer*& renderer);
	void reset(SDL_Renderer*& renderer);
	void dead(SDL_Renderer*& renderer);
	void ramasse(SDL_Renderer*& renderer);
	bool getIsfiring(){return Isfiring;}
	void setIsfiring(bool b){Isfiring=b;}
	void setWeapon(int i);
	unsigned int getIdWeapon(){return id_weapon;}
private:
	unsigned int id_weapon = 0; // 0 : arme par défaut , 1 : bazooka , 2 : sayen
	bool Isfiring=false;
};

#endif
