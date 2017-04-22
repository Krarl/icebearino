#include "icefloe.h"
#include "game.h"
#include "util.h"

Part::Part(){

}

Icefloe::Icefloe(){
	set<pair<int, int> > taken;
	parts.push_back(Part());
	pos = V2f(0, 0);
	vel = V2f(0.5f-rnd(), 0.5f-rnd());
}

void Icefloe::update(Game* game){
	pos += game->dt*vel;
}

void Icefloe::render(Game* game){
	for (Part part : parts){
		Polygon pol = part.polygon;
		sf::ConvexShape cs(pol.points.size());
		rep(i, 0, pol.points.size())
			cs.setPoint(i, pol.points[i]);
		cs.setPosition(game->center+game->screenCenter+pos);
		game->window->draw(cs);
	}
}
