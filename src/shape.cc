#include <iostream>
#include <string>
#include "../lib/shape.hh"

Shape::Shape():_x(0), _y(0){

}

Shape::Shape(double x, double y):_x(x), _y(y){

}

Shape::~Shape(){
	std::cout << "~S" << std::endl;
}

double Shape::getX(){
	return _x;
}

double Shape::getY(){
	return _y;
}

void Shape::setX(double new_x){
	_x=new_x;
}

void Shape::setY(double new_y){
	_x=new_y;
}

void Shape::setPosition(double new_x, double new_y){
	this->setX(new_x);
	this->setY(new_y);
}