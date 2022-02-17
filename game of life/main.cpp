#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

int main()
{
	Game game;
	while (game.isrunning())
	{
		game.update();

		game.render();
	}
	

	

	return 0;
}