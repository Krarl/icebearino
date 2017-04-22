#include "icefloe.h"
#include "game.h"
#include "util.h"
#include "macros.h"
#include <math.h>

vector<V2f> circlePoints(int n, float r, float randf = 0){
	vector<V2f> ret;
	float ang = rnd()*2*M_PI;
	rep(i, 0, n)
		ret.push_back(V2f(r*(cos(2*M_PI*i/n+ang)+(rnd()-0.5f)*randf)
			, r*(sin(2*M_PI*i/n+ang)+(rnd()-0.5f)*randf)));
	return ret;
}

Part::Part(){

}

Part::Part(vector<V2f> pol){
	polygon = Polygon(pol);
}


Icefloe::Icefloe(V2f pos, int ind) {
	this->ind = ind;
	set<pair<int, int> > taken;
	this->pos = pos;
	vel = V2f(0.5f-rnd(), 0.5f-rnd())*100.f;

	float radrnd = rnd();
	rad = 10+radrnd*80;

	parts.push_back(Part(circlePoints(5, rad, 0.2f)));

	vector<V2f> circle = circlePoints(int(2+7*rnd()*radrnd), rad*0.8);
	for(V2f p : circle){
		vector<V2f> blob = circlePoints(int(3+3*rnd()), rad*(0.3+rnd()*0.2), 0.5);
		for (V2f& point : blob)
			point += p;
		parts.push_back(Part(blob));
	}

	mass = 0;
	for (Part part : parts)
		mass += part.polygon.area();
}

Icefloe::Icefloe() : Icefloe(V2f(0, 0), 0) {

}


void Icefloe::update(Game* game){
	pos += game->dt*vel;

	for(auto it = next(game->icefloes.find(ind)); it != game->icefloes.end(); it++){
		Icefloe* icefloe = it->second;
		if (icefloe == this)
			continue;
		
		if (rad+icefloe->rad > len(icefloe->pos-pos)){
			float m1 = mass, m2 = icefloe->mass, u1 = len(vel), u2 = len(icefloe->vel);
			V2f v1 = norm(icefloe->vel)*(u1*(m1-m2)+2*m2*u2)/(m1+m2);
			V2f v2 = norm(vel)*(u2*(m2-m1)+2*m1*u1)/(m1+m2);
			vel = v1;
			icefloe->vel = v2;
		}
	}
}

void Icefloe::render(Game* game){
	for (Part part : parts){
		Polygon pol = part.polygon;
		sf::ConvexShape cs(pol.points.size());
		rep(i, 0, pol.points.size())
			cs.setPoint(i, pol.points[i]);
		cs.setPosition(-game->center+game->screenCenter+pos);
		game->window->draw(cs);
	}
}

bool Icefloe::inside(V2f point, bool precise){
	bool yes = false;
	for(Part part : parts){
		yes |= part.polygon.inside(point);
		if (!precise)
			break;
	}
	return yes;
}
