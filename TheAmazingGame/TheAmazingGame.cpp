#include "TheAmazingGame.h"
#include <fstream>
#include <string>
TheAmazingGame::TheAmazingGame() : player(maze,1,2) {
	std::ifstream saveFile("Save.txt");
	if (saveFile.is_open())
	{
		std::string tempStr;
		saveFile >> tempStr;
		hiScore = std::stoi(tempStr);
	}
	else
		hiScore = 0;
}
void TheAmazingGame::Save() {
	if (hiScore > score)
		return;
	std::ofstream saveFile;
	saveFile.open("Save.txt");
	saveFile << score;
}
void TheAmazingGame::Play() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	score = 0;
	isPlaying = true;

	WriteScore();
	maze.WriteMaze();
	player.WritePlayer();

	while (isPlaying)
	{
		Uppdate();
		Sleep(50);
	}
}
void TheAmazingGame::Uppdate() {
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		isPlaying = false;
		system("CLS");
	}

	player.MoveUppdate();
	if (player.isInGoal)
		MazeFinished();
}
void TheAmazingGame::MazeFinished() {
	system("CLS");
	score++;
	if (score > hiScore)
		hiScore = score;
	WriteScore();
	Save();

	maze.ClearMaze();
	maze.GenerateMaze();
	maze.WriteMaze();

	player.isInGoal = false;
	player.ResetPositon();
	player.WritePlayer();
}
void TheAmazingGame::WriteScore() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
	std::cout<<"Hiscore: "<< hiScore << " Score: " << score << '\n';
}