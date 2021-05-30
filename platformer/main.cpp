#include "stdafx.h"
#include "Game.h"
#include"MainMenu.h"

int main()
{
	srand(time(0));

	MainMenu menu;

	while (menu.getWindow().isOpen())
	{
		menu.update();
		menu.render();
	}
	if (!menu.getWindow().isOpen())
	{
		Game game;
		while (game.getWindow().isOpen())
		{
			game.update();
			game.render();
		}
	}




}
