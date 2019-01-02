#pragma once

#include "Ray.h"
#include "Light.h"

//typedef unsigned char RGBApixel[4];
struct RGBApixel {
	unsigned char r, g, b, a;
};

// Represents a genric object. This is a virtual class and no object of the class
// can be created. Other shapes will be a subclass of this function and they
// must implement the function to determine if a ray intersects with the object.
class Objects {
public:
	// Determines if a ray intersects with an object. Will return -1 if no hit founds
	virtual double hit(Ray &ray) {
		return -1;
	}

	// Returns the color of the object
	RGBApixel getColor() {
		return color;
	}

	RGBApercentage ambient;
	RGBApercentage diffuse;
	RGBApercentage specular;
	RGBApixel color;	// Color of the object
	double shinyness;

	double x;		// x location in the world
	double y;		// y location in the world
	double z;		// z location in the word

protected:
	Matrix matrix;	// Matrix representing transformation of the current object
};