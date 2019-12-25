#include <iostream>
#include <string>
#include "../lib/personnage.hh"

Personnage::Personnage(): Shape(){
  _vie=100;
  _stamina=100;
  _vivant=true;
}

void Personnage::update(){
	_vie -= 1;
}

Personnage::~Personnage(){
	std::cout << "~P" << std::endl;
}
