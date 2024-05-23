#include "TheAmazingGame.h"
#include "BitFunctions.h"

int main()
{
	srand((unsigned)time(NULL));
	TheAmazingGame game;
	game.Play();
	game.Save();

	/* TestStuff
	BitFunctions bitFun;
	unsigned char firt = 0b10101011;
	unsigned char secound = 0b11011111;
	bitFun.WriteAllBits(firt);
	std::cout << " ^\n";
	bitFun.WriteAllBits(secound);
	std::cout << "\n\n";  
	bitFun.WriteAllBits((unsigned char)(firt^secound));*/
}