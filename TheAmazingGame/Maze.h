#pragma once
#include "BitFunctions.h"
#include "MazeChecks.h"
#include "Direction.h"
#include <Windows.h>
#include <iostream>
template <unsigned int sizeX, unsigned int sizeY>
class Maze : public MazeChecks
{
public:
	Maze();
	void ClearMaze();
	void GenerateMaze();
	void WriteMaze();
	void AddWall(Position pos);
	void AddWall(unsigned int x, unsigned int y);
	void RemoveWall(Position pos);
	void RemoveWall(unsigned int x, unsigned int y);
	bool WallExitAt(Position pos);
	bool WallExitAt(unsigned int x, unsigned int y);
	bool IsGoalAt(Position pos);
	bool IsGoalAt(unsigned int x, unsigned int y);
	// Symbols
	char floorSym = ' ';
	char wallSym = 219;
	char edgeSym = 219;
	char goalSym = 219;
private:
	Position snakePath[sizeX * sizeY]; // used for remembering where walls has been removed so it can walk back
	unsigned int finalPathLength;

	unsigned int bytesLength = sizeX / 8 + (bool)(sizeX % 8);
	short finalByteLength = sizeX % 8;
	unsigned char bytes[sizeX / 8 + (bool)(sizeX % 8)][sizeY]; // muliy array for wall/emty

	void ResetDir(unsigned char&);
	unsigned char GetDir(unsigned char&);
};

template <unsigned int sizeX, unsigned int sizeY>
Maze<sizeX, sizeY>::Maze() {
	if (sizeX <= 1)
	{
		std::cerr << "sizeX of Maze Must me bigger then 1. current value: "<<sizeX;
		exit(-1);
	}
	else if (sizeY <= 1)
	{
		std::cerr << "sizeY of Maze Must me bigger then 1. current value: " << sizeY;
		exit(-1);
	}
	ClearMaze();
	GenerateMaze();
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::ClearMaze() {
	for (size_t y = 0; y < sizeY; y++)
	{
		for (size_t x = 0; x < bytesLength; x++)
		{
			bytes[x][y] = ~0;
		}
	}
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::GenerateMaze() {

	Position beginingPos(0,0);
	Position snakePos(beginingPos.x+1, beginingPos.y);
	unsigned char xBitPos = 1;
	bytes[beginingPos.x >> 3][beginingPos.y] &= ~(0b11 << beginingPos.x % 8);

	unsigned int pathIndex = 2;
	finalPathLength = 1;

	snakePath[0] = beginingPos;
	snakePath[1] = snakePos;

	unsigned char dir = ~0;
	while (pathIndex != 0)
	{
		Direction moveDir;
		if (beginingPos == snakePos)
		{
			break;
		}
		switch (GetDir(dir))
		{
		case 0:
			ResetDir(dir);
			pathIndex--;
			snakePos = snakePath[pathIndex];
			break;
		case 1:
			moveDir.y = 1;
			break;
		case 0b10:
			if (snakePos.y != 0)
				moveDir.y = -1;
			break;
		case 0b100:
			moveDir.x = 1;
			break;
		case 0b1000:
			if (snakePos.x != 0)
				moveDir.x = -1;
			break;
		}
		
		unsigned char checkMidle = 0;
		if (moveDir.y != 0)
		{
			unsigned char row = snakePos.x >> 3;
			if (moveDir.y == 1 && snakePos.y == sizeY - 1)
				continue;

			if ((snakePos.x % 8) == 0 && snakePos.x != 1)
			{
				checkMidle = 0b11;
				if (~bytes[row - 1][snakePos.y + moveDir.y] & 0b10000000)
				{
					continue;
				}
			}
			else if ((snakePos.x % 8) == 0)
			{
				checkMidle = 0b11;
			}

			else if ((snakePos.x % 8) == 7 && snakePos.x != sizeX-1)
			{
				checkMidle =0b11000000;
				if (~bytes[row + 1][snakePos.y + moveDir.y] & 0b1)
				{
					continue;
				}
			}
			else if ((snakePos.x % 8) == 7)
			{
				checkMidle = 0b11000000;
			}
			else
			{
				checkMidle = 0b111 << (snakePos.x % 8 - 1);
			}

			if (~bytes[row][snakePos.y+moveDir.y] & checkMidle) {
				continue;
			}
			else if (moveDir.y == -1 && snakePos.y >= 2 && (~bytes[row][snakePos.y - 2] & (1 << snakePos.x % 8)))
			{
				continue;
			}
			else if (moveDir.y == 1 && snakePos.y + 2 < sizeY && (~bytes[row][snakePos.y + 2] & (1 << snakePos.x % 8))) {
				continue;
			}
			else
			{
				if (pathIndex > finalPathLength)
					finalPathLength = pathIndex;

				snakePos += moveDir;
				snakePath[pathIndex] = snakePos;
				pathIndex++;
				ResetDir(dir);

				bytes[row][snakePos.y] -= 1 << snakePos.x % 8;
			}
		}
		else if (moveDir.x != 0)
		{
			unsigned int posDirX = snakePos.x + moveDir.x;
			unsigned char row = posDirX >> 3;

			checkMidle = (0b11 << (posDirX % 8));
			if (moveDir.x == -1)
				checkMidle >>= 1;

			if (rand() % 10 == 0 && snakePos.x != 0 && snakePos.x != sizeX-1)
			{ }
			else if (snakePos.y != 0 && ~bytes[row][snakePos.y - 1] & (1 << posDirX % 8))
			{
				continue;
			}
			else if (snakePos.y != sizeY - 1 && ~bytes[row][snakePos.y + 1] & (1 << posDirX % 8)) {
				continue;
			}

			else if ((moveDir.x == -1 && posDirX % 8 == 0 && posDirX != 0) && (~bytes[row - 1][snakePos.y] & 0b10000000))
			{
				continue;
			}
			else if ((moveDir.x == 1 && posDirX % 8 == 7 && posDirX != sizeX-1) && (~bytes[row + 1][snakePos.y] & 0b1))
			{
				continue;
			}
			else if (moveDir.x == 1 && snakePos.x == sizeX - 1 && snakePos.x % 8 == finalByteLength-1)
			{
				continue;
			}
			
			if (!(~bytes[row][snakePos.y] & checkMidle))
			{
				if (pathIndex > finalPathLength)
					finalPathLength = pathIndex;

				snakePos += moveDir;
				snakePath[pathIndex] = snakePos;
				pathIndex++;
				ResetDir(dir);
				bytes[row][snakePos.y] -= 1 << snakePos.x % 8;
			}
		}

		// Debuging maze snake
		/*system("cls");
		std::cout << "{ " << snakePos.x << ", " << snakePos.y << " }\n";
		WriteMaze();
		while (!(GetKeyState(VK_RETURN) < 0)) {
		}
		Sleep(80);*/
	}
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::WriteMaze() {

	for (size_t y = 0; y < sizeX+2; y++)
		std::cout << edgeSym;
	std::cout << std::endl;

	for (size_t y = 0; y < sizeY; y++)
	{
		for (size_t x = 0; x < bytesLength; x++)
		{
			if (x == 0)
				std::cout << edgeSym;

			short writeLength;
			if (x == bytesLength - 1 && finalByteLength != 0)
				writeLength = finalByteLength;
			else
				writeLength = 8;

			unsigned char value = bytes[x][y];

			for (size_t i = 0; i < writeLength; i++)
			{
				if (value & 1)
					std::cout << wallSym;
				else
					std::cout << floorSym;

				value = value >> 1;
			}
		}
		std::cout << edgeSym << std::endl;
	}

	for (size_t y = 0; y < sizeX + 2; y++)
		std::cout << edgeSym;

	COORD cord = { snakePath[finalPathLength].x+1,snakePath[finalPathLength].y + 2 };
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, 2);
	SetConsoleCursorPosition(out, cord);
	std::cout << goalSym;
	SetConsoleTextAttribute(out, 7);
}

template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::AddWall(Position pos) {
	if (!(bytes[pos.x >> 3][pos.y] & 1 << pos.x % 8))
		bytes[pos.x >> 3][pos.y] += 1 << pos.x % 8;
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::AddWall(unsigned int x, unsigned y) {
	if (!(bytes[x >> 3][y] & 1 << x % 8))
		bytes[x >> 3][y] += 1 << x % 8;
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::RemoveWall(Position pos) {
	if (bytes[pos.x >> 3][pos.y] & 1 << pos.x % 8)
		bytes[pos.x >> 3][pos.y] -= 1 << pos.x % 8;
}
template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::RemoveWall(unsigned int x, unsigned y) {
	if (bytes[x >> 3][y] & 1 << x % 8)
		bytes[x >> 3][y] -= 1 << x % 8;
}
template <unsigned int sizeX, unsigned int sizeY>
bool Maze<sizeX, sizeY>::WallExitAt(Position pos) {
	if (pos.x < 0 || pos.x >= sizeX || pos.y < 0 || pos.y >= sizeY)
		return true;
	else if (bytes[pos.x >> 3][pos.y] & 1 << pos.x % 8)
		return true;
	else
		return false;
}
template <unsigned int sizeX, unsigned int sizeY>
bool Maze<sizeX, sizeY>::WallExitAt(unsigned int x, unsigned y) {
	if (bytes[x >> 3][y] & 1 << x % 8)
		return true;
	else
		return false;
}
template <unsigned int sizeX, unsigned int sizeY>
bool Maze<sizeX, sizeY>::IsGoalAt(Position pos) {
	if (pos == snakePath[finalPathLength])
		return true;
	else
		return false;
}
template <unsigned int sizeX, unsigned int sizeY>
bool Maze<sizeX, sizeY>::IsGoalAt(unsigned int x, unsigned y) {
	if (snakePath[finalPathLength].x == x && snakePath[finalPathLength].y == y)
		return true;
	else
		return false;
}

template <unsigned int sizeX, unsigned int sizeY>
void Maze<sizeX, sizeY>::ResetDir(unsigned char& dir) {
	dir = ~0;
}
template <unsigned int sizeX, unsigned int sizeY>
unsigned char Maze<sizeX, sizeY>::GetDir(unsigned char& dir) {
	
	short dirValuesLeft = 5;
	unsigned char rndValue = 1 << rand() % 4;
	while (true)
	{
		if (dir & rndValue)
		{
			dir -= rndValue;
			return rndValue;
		}
		else
		{
			if (dirValuesLeft == 0)
				break;
			else
				dirValuesLeft--;

			if (rndValue == 0b1000)
				rndValue = 1;
			else
				rndValue <<= 1;
		}
	}
	return 0;
}