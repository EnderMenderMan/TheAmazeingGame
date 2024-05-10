#include "TheAmazingGame.h"

int main()
{
	srand((unsigned)time(NULL));
	TheAmazingGame game;
	game.Play();
	game.Save();
}