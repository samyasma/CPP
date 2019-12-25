#ifndef SMOKE_HPP_
#define SMOKE_HPP_

#include <iostream>
#include <string>
#include "smoke.hh"

class Smoke : public Personnage{
public:
	Smoke();
	~Smoke(){std::cout << "~Sm" << std::endl;}
	Smoke():Personnage(0,0,50,50, "./images/smoke.png"){id += 1;}
private:
	int id;
};

#endif