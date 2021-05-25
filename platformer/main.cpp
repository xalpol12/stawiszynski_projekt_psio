#include "stdafx.h"
#include "Game.h"

int main()
{
	srand(time(0));
	Game game;

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}
}
