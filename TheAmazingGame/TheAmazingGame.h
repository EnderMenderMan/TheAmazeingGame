#pragma once
#include "Maze.h"
#include "Player.h"
class TheAmazingGame
{
public:
	TheAmazingGame();
	void Save();
	void Play();
private:
	void Uppdate();
	void MazeFinished();
	void WriteScore();
	bool isPlaying;
	unsigned int score;
	unsigned int hiScore;
	Maze<18, 18> maze;
	Player player;

};

