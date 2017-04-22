#include "perlin.h"
#include "util.h"

float myRand(piii seed, int c){
	int sd = 134453245+seed.FST*2341+seed.SND*345647+seed.TRD*45431+c*7;
	/*
	return (sd*100000007LL%int(1e9+7)+int(1e9+7))/float(1e9+7);*/
	srand(sd);
	return rnd();
}

V3f randVec(piii p){
	return V3f(myRand(p, 0)-0.5, myRand(p, 1)-0.5, myRand(p, 2)-0.5)*2.f;
}

float Perlin::smooth(float a, float b, float f){
	return b*f+a*(1-f);
}

float dot(V3f a, V3f b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float Perlin::perlAt(V3f p){
	p *= scale;
	int x = floor(p.x), y = floor(p.y), z = floor(p.z);
	float xf = p.x-x, yf = p.y-y, zf = p.z-z;

	vector<float> dots(8);
	rep(i, 0, 8){
		bool xa = i&1, ya = i&2, za = i&4;
		V3f dist(xa ? 1-xf : xf, ya ? 1-yf : yf, za ? 1-zf : zf);
		dots[i] = dot(dist, randVec(MT(x+xa, y+ya, z+za)));
	}

	float p_00 = smooth(dots[0+0+0], dots[0+0+4], zf);
	float p_10 = smooth(dots[1+0+0], dots[1+0+4], zf);
	float p_01 = smooth(dots[0+2+0], dots[0+2+4], zf);
	float p_11 = smooth(dots[1+2+0], dots[1+2+4], zf);

	float p_0 = smooth(p_00, p_01, yf);
	float p_1 = smooth(p_10, p_11, yf);

	return smooth(p_0, p_1, xf);
}
