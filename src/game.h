#ifndef GAME_H_
#define GAME_H_
#include <map>
#include "penguin.h"
#include "player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "icefloe.h"
#include "particlesystem.h"
using namespace std;

class Penguin;
class Player;

class Game {
public:
	sf::RenderWindow* window;
	V2f center, screenCenter;
	Player* player;
	string menuText = "";
	vector<Penguin*> penguins;
	map<int, Icefloe*> icefloes;
	float dt;
	bool over;
	int score;

	void init(sf::RenderWindow* window);
	void cleanup();
	void update(float dt);
	void render();

	void addPenguinOnFloe(int floe);
	void addBloodAt(sf::Vector2f pos);

private:
	sf::Texture waterTexture;
	sf::Sprite water;

	sf::SoundBuffer penguinDeathBuffer;
	sf::Sound penguinDeath;

	sf::SoundBuffer chompBuffer;
	sf::Sound chomp;

	vector<ParticleSystem*> bloodSplashes;
};

#endif
