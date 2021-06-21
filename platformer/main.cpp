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
	if (!menu.getWindow().isOpen()&&menu.wasEscapePressed()==false)
	{
		Game game(10, 2 ,menu.selectedMap); //first int is music volume and the second is audio effects volume (recommended - music: 5, audio: 3)
		while (game.getWindow().isOpen())
		{
			if (game.getPlayerHp() > 0)
			{
				game.update();
				game.render();
			}
			else
				game.over();
		}
	}




}
