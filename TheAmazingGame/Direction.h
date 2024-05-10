#pragma once
#include "Basic2D.h"
class Direction : public Basic2D<int>
{
public:
	Direction() : Basic2D(){}
	Direction(const int& x,const int& y) : Basic2D(x, y){}
	//int x;
	//int y;
};

