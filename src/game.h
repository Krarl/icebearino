#ifndef GAME_H_
#define GAME_H_
#include <map>
#include "penguin.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Penguin;

class Game {
public:
	void init();
	map<int, Penguin*> penguins;
	sf::Window* window;
	float dt;

	void update(float dt);
	void render();

};

#endif