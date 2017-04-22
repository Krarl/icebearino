#include "game.h"
#include <iostream>
#include <string> 
#include "macros.h"
using namespace std;

void Game::init(sf::RenderWindow* window){
	cout << "hej" << endl;
	this->window = window;
	center = V2f(0, 0);
	screenCenter = V2f(800, 600);
}

void Game::update(float dt){
	this->dt = dt;
	for (auto p : penguins)
		p.second->update(this);
}


void Game::render(){

}