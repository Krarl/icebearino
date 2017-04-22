#ifndef GAME_H_
#define GAME_H_
#include <map>
#include "penguin.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "icefloe.h"
using namespace std;

class Penguin;

class Game {
public:
	sf::RenderWindow* window;
	V2f center, screenCenter;
	vector<Penguin*> penguins;
	map<int, Icefloe*> icefloes;
	float dt;

	void init(sf::RenderWindow* window);
	void update(float dt);
	void render();

private:
	sf::Texture waterTexture;
	sf::Sprite water;
};

#endif
