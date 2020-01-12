#ifndef SAMY_HPP_
#define SAMY_HPP_

#include <iostream>
#include <string>
#include "../lib/personnage.hh"

class Samy : public Personnage{
public:
	//Smoke();
	~Samy();
	Samy();
	Samy(double x, double y,unsigned int id);
	void update(SDL_Event event, SDL_Renderer*& renderer);
	void update();
	void decrease();
	void Attack(SDL_Renderer*& renderer);
	void reset(SDL_Renderer*& renderer);
	void dead(SDL_Renderer*& renderer);
	void ramasse(SDL_Renderer*& renderer);
	bool getIsfiring();
	void setIsfiring(bool b);
	void setWeapon(int i);
	unsigned int getIdWeapon();
	void walk(SDL_Renderer*& renderer);
private:
	unsigned int id_weapon = 0; // 0 : arme par défaut , 1 : bazooka , 2 : sayen
	bool Isfiring=false;
	unsigned int _id;
	double id_walk = 2.0;
};

#endif
