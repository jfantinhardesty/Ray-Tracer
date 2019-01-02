#pragma once

#include "Matrix.h"

const int GLOBAL = 0;
const int POINTLIGHT = 1;
const int DIRECTIONAL = 2;
const int SPOTLIGHT = 3;

struct RGBApercentage {
	double r, g, b, a;
};

class Light {
public:
	// Constructor for spotlight
	Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, double exp, double ang, Point &pos, Vector &dir);
	
	Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, Vector &dir);

	// Constructor for point light
	Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, Point &pos);

	// Constructor for global light
	Light(RGBApercentage &amb);

	int type;
	RGBApercentage ambient;
	RGBApercentage diffuse;
	RGBApercentage specular;
	double exponent;
	double angle;
	Point position;
	Vector direction;
};