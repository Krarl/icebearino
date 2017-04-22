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
	water.setTexture(waterTexture);
	water.setRepeated(true);
	water.setSize(800, 600);
}

void Game::update(float dt){
	this->dt = dt;
	for (auto p : penguins)
		p->update(this);
}


void Game::render(){
	

	for (auto p : penguins)
		penguin->render();

	
}