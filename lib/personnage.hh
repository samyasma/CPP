#ifndef PERSONNAGE_HPP_
#define PERSONNAGE_HPP_

#include <iostream>
#include <string>
#include "shape.hh"

class Personnage: public Shape{
  public :
  Personnage();
  Personnage(double x, double y, int vie, int stamina):Shape(x, y){_vie = vie; _stamina = stamina; _vivant = true;}
  void Attack();
  void Defense();
  virtual ~Personnage();
  void update();
  void Jump();
  void DoDamage();
  void TakeDamage();

  protected:
    int _vie;
    int _stamina;
    bool _vivant;
};

#endif