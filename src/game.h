#ifndef GAME_H_
#define GAME_H_
#include <map>
#include "penguin.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "macros.h"
using namespace std;

class Penguin;

class Game {
public:
	void init(sf::RenderWindow* window);
	map<int, Penguin*> penguins;
	sf::RenderWindow* window;
	V2f center, screenCenter;

	float dt;

	void update(float dt);
	void render();

};

#endif