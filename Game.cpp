#pragma once
#include "Game.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void Game::initWindow()
{
	videomode.height = 850;
	videomode.width = 850;
	window = new sf::RenderWindow(videomode, "Game of Life");
	window->setFramerateLimit(60);
	view.setCenter(425, 425);
	window->setView(view);
	moving = false;
}

void Game::initVariables()
{
	texture_alive.loadFromFile("alive.png");
	texture_dead.loadFromFile("dead.png");

	tile_alive.setTexture(texture_alive);
	tile_dead.setTexture(texture_dead);

	cols = 25;
	rows = 25;

	tiles = new bool*[cols];

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			tiles[i] = new bool[rows];
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			tiles[i][j] = false;
		}
	}

	tiles_next = new bool* [cols];

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			tiles_next[i] = new bool[rows];
		}
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			tiles_next[i][j] = false;
		}
	}

	
	
	srand(time(NULL));

	int temp;

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			temp = rand() % 2;
			if (temp == 0)
			{
				tiles[i][j] = false;
			}
			else
			{
				tiles[i][j] = true;
			}
		}
	}
	
}

Game::Game()
{
	initWindow();
	initVariables();
}

Game::~Game()
{
	delete window;
}

const bool Game::isrunning() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while(window->pollEvent(ev))
	{
		mouse = sf::Mouse::getPosition(*window);
		
		switch (ev.type)
		{
		case::sf::Event::KeyPressed: 
			if (ev.key.code == sf::Keyboard::Right)
			{
				update_next();
			}
			break;
		case::sf::Event::MouseButtonPressed:
			if (ev.key.code == sf::Mouse::Left)
			{
				change_on_click();
			}
			else if (ev.key.code == sf::Mouse::Middle)
			{
				moving = true;
				oldPos = sf::Mouse::getPosition(*window);
				temp_center = sf::Vector2i(view.getCenter().x, view.getCenter().y);
			}
			break;
		case::sf::Event::MouseMoved:
			if (moving)
			{
				newPos = sf::Mouse::getPosition(*window);
				sf::Vector2i temp = oldPos - newPos;
				view.setCenter(temp.x + temp_center.x, temp.y + temp_center.y);
				window->setView(view);
			}
			break;
		case::sf::Event::MouseButtonReleased:
			if (ev.key.code == sf::Mouse::Middle)
			{
				moving = false;
			}
			break;



		case::sf::Event::Closed:
			window->close();
			break;
		}
	}

}

void Game::update()
{
	pollEvents();
}

void Game::render()
{
	window->clear(sf::Color::Black);

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (tiles[i][j] == false)
			{
				tile_dead.setPosition(i * 32, j * 32);
				window->draw(tile_dead);
			}
			else
			{
				tile_alive.setPosition(i * 32, j * 32);
				window->draw(tile_alive);
			}
		}
	}

	window->display();
}

void Game::update_next()
{	
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (i == 0 || j == 0 || i == cols - 1 || j == rows - 1)
			{
				continue;
			}
			else
			{
				int neighbors = count_neighbors(i, j);

				switch (tiles[i][j])
				{
				case false:
					if (neighbors == 3)
					{
						tiles_next[i][j] = true;
					}
					else
					{
						tiles_next[i][j] = false;
					}
					break;
				case true:
					if (neighbors < 2 || neighbors > 3)
					{
						tiles_next[i][j] = false;
					}
					else
					{
						tiles_next[i][j] = true;
					}
					break;
				}
		
				
			}
		}
	}
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (i == 0 || j == 0 || i == cols - 1 || j == rows - 1)
			{
				continue;
			}
			tiles[i][j] = tiles_next[i][j];
		}
	}

}

int Game::count_neighbors(int x, int y)
{
	int count = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			else if (tiles[x + i][y + j] == true)
			{
				count++;
			}
		}
	}

	return count;
}

void Game::change_on_click()
{
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	int x = floor(mouse_world.x/32);
	int y = floor(mouse_world.y/32);
	if (tiles[x][y] == false)
	{
		tiles[x][y] = true;
	}
	else
	{
		tiles[x][y] = false;
	}
}


