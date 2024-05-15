#include "Player.h"
Player::Player(MazeChecks& checks, unsigned int startX, unsigned int startY) : mChecks(checks) {
	startPos.x = startX;
	startPos.y = startY;
	pos = Position(0, 0);
	COORD cord = { startPos.x,startPos.y};
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, color);
	SetConsoleCursorPosition(out, cord);
	std::cout << skin;
	SetConsoleTextAttribute(out, 7);
}
void Player::MoveUppdate(){
	if (GetKeyState('W') < 0)
		Checks(0,-1);
	if (GetKeyState('S') < 0)
		Checks(0,1);
	if (GetKeyState('D') < 0)
		Checks(1,0);
	if (GetKeyState('A') < 0)
		Checks(-1,0);
}
void Player::ResetPositon() {
	pos = Position(0,0);
}
void Player::WritePlayer() { 
	COORD cord = { startPos.x,startPos.y };
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, color);
	SetConsoleCursorPosition(out, cord);
	std::cout << skin;
	SetConsoleTextAttribute(out, 7);
}
void Player::Checks(int x, int y) {
	Direction dir(x, y);
	Position tempPos = pos + dir;

	if (mChecks.IsGoalAt(tempPos)) {
		isInGoal = true;
	}
	else if (!mChecks.WallExitAt(tempPos))
	{
		pos += dir;

		std::cout << "\b ";
		COORD cord = { pos.x+startPos.x,pos.y+startPos.y };
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(out, color);
		SetConsoleCursorPosition(out, cord);
		std::cout << skin;
		SetConsoleTextAttribute(out, 7);
	}
}
