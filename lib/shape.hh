#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Shape{
public:
	Shape():_x(0), _y(0){}
	Shape(double x, double y):_x(x), _y(y){}
	virtual ~Shape(){std::cout << "~S" << std::endl;}
	virtual void update(SDL_Event event) = 0;
	double getX(){return _x;}
	double getY(){return _y;}
protected:
	double _x;
	double _y;
};

#endif