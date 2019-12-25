#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <iostream>
#include <string>

class Shape{
public:
	Shape():_x(0), _y(0){}
	Shape(double x, double y):_x(x), _y(y){}
	virtual ~Shape(){std::cout << "~S" << std::endl;}
	virtual void update() = 0;
protected:
	double _x;
	double _y;
};

#endif