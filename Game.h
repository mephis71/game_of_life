#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <stdlib.h>
#include <time.h>



class Game
{
private:
	//Window and view

	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;
	sf::View view;
	bool moving;
	sf::Vector2i oldPos;
	sf::Vector2i newPos;
	sf::Vector2i temp_center;

	//Mouse

	sf::Vector2i mouse;
	
	//Initializers

	void initWindow();
	void initVariables();

	//Tiles

	int cols, rows;
	bool** tiles;
	bool** tiles_next;
	sf::Sprite tile_alive;
	sf::Sprite tile_dead;

	sf::Texture texture_alive;
	sf::Texture texture_dead;
	
public:

	//Constructor and destructor
	Game();
	~Game();

	//Functions (rendering, updating, event polling, etc.)

	const bool isrunning() const;

	void pollEvents();
	void update();

	void render();

	//Game functions

	void update_next();
	int count_neighbors(int x, int y);
	void change_on_click();

	





};
