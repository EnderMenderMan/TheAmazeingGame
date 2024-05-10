#pragma once
#include "Position.h"
class MazeChecks
{
public:
	virtual bool WallExitAt(Position pos) = 0;
	virtual bool WallExitAt(unsigned int x, unsigned int y) = 0;
	virtual bool IsGoalAt(Position pos) = 0;
	virtual bool IsGoalAt(unsigned int x, unsigned int y) = 0;
};