#pragma once
#include "Direction.h"
#include"Basic2D.h"
class Position : public Basic2D<unsigned int>
{
public:
	Position() : Basic2D(){}
	Position(const unsigned int& x,const unsigned int& y) : Basic2D(x,y){}
	Position(Position& pos) : Basic2D(pos){}
	void Add(const Direction& dir);
	void operator+=(const Direction&);
	Position operator+(const Direction&);
};

