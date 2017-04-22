#include "polygon.h"
#include "macros.h"

Polygon::Polygon(){
	float len = 10;
	points.push_back(V2f(-len, -len));
	points.push_back(V2f(len, -len));
	points.push_back(V2f(len, len));
	points.push_back(V2f(-len, len));
}


Polygon::Polygon(vector<V2f> points){
	this->points = points;
}
