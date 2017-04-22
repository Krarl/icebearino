#include "game.h"
#include "util.h"
#include <iostream>
#include <string>
#include "macros.h"
using namespace std;

void Game::init(sf::RenderWindow* window){
	cout << "hej" << endl;
	this->window = window;
	center = V2f(0, 0);
	screenCenter = V2f(400, 300);

	loadTexture(waterTexture, "res/img/water.png");
	waterTexture.setRepeated(true);
	water.setTexture(waterTexture);
	water.setTextureRect(sf::IntRect(0, 0, 800, 600));
	icefloes[0] = new Icefloe();
}

void Game::update(float dt){
	this->dt = dt;
	for (auto penguin : penguins)
		penguin->update(this);
}


void Game::render(){
	window->draw(water);

	for (auto penguin : penguins)
		penguin->render(this);


}
