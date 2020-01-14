#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Shape{
public:
	Shape();
	Shape(double x, double y);
	virtual ~Shape();
	virtual void update(SDL_Event event, SDL_Renderer*& renderer) = 0;
	double getX();
	double getY();
	void setX(double new_x);	
	void setY(double new_y);
	void setPosition(double new_x, double new_y);
protected:
	double _x;
	double _y;
	SDL_Surface* surface;
};

#endif
