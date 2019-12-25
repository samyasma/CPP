#pragma once
#include <iostream>
#include <string>

class Personnage {
  public :
  Personnage();
  void Attack();
  void Defense();
  virtual ~Personnage();
  void Jump();
  void DoDamage();
  void TakeDamage();

  protected:
    int vie;
    int stamina;
    bool vivant;
}
