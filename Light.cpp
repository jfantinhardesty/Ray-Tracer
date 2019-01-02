
#include "Light.h"

Light::Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, double exp, double ang, Point &pos, Vector &dir) {
	type = SPOTLIGHT;
	ambient = amb;
	diffuse = dif;
	specular = spec;
	exponent = exp;
	angle = ang;
	position = pos;
	direction = dir;
}

Light::Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, Vector &dir) {
	type = DIRECTIONAL;
	ambient = amb;
	diffuse = dif;
	specular = spec;
	direction = dir;
}

Light::Light(RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, Point &pos) {
	type = POINTLIGHT;
	ambient = amb;
	diffuse = dif;
	specular = spec;
	position = pos;
}

Light::Light(RGBApercentage &amb) {
	type = GLOBAL;
	ambient = amb;
	diffuse = { 0,0,0,1 };
	specular = { 0,0,0,1 };
}