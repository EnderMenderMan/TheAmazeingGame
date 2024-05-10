#pragma once
#include "Position.h"
#include "Maze.h"
class Player
{
public:
	Player(MazeChecks& checks,unsigned int startX, unsigned int startY);
	void MoveUppdate();
	void ResetPositon();
	void WritePlayer();
	char skin = 254;
	int color = 5;
	bool isInGoal = false;
private:
	void Checks(int x,int y);
	MazeChecks& mChecks;
	Position pos;
	Position startPos;
};

