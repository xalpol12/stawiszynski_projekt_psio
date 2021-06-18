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
		Game game(10,3); //TODO: Options menu with volume selection
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
