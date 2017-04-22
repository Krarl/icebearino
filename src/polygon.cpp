#include "polygon.h"
#include "macros.h"

Polygon::Polygon(){
	float len = 50;
	points.push_back(V2f(-len, -len));
	points.push_back(V2f(len, -len));
	points.push_back(V2f(len, len));
	points.push_back(V2f(-len, len));
}

Polygon::Polygon(vector<V2f> points){
	this->points = points;
}

bool Polygon::inside(V2f point){
	bool yes = true;
	rep(i, 0, points.size()){
		V2f edge = points[(i+1)%points.size()]-points[i], place = point-points[i];
		yes &= edge.y*place.x-edge.x*place.y <= 0;
	}
	return yes;
}

float Polygon::area(){
	float ret = 0;
	rep(i, 0, points.size()){
		V2f p1 = points[i], p2 = points[(i+1)%points.size()];
		ret += p1.x*p2.y-p1.y*p2.x;
	}
	return ret;
}
