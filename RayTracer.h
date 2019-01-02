#pragma once

#include "Sphere.h"
#include "Light.h"

// Structure that holds the index in the array of objects that an array intersects with
// a time of the hit and the number of times the ray hit something
struct hitInfo {
	int index;
	double hit;
	int numHits;
};

// The ray tracer class is responsible for iterating through a list of objects and 
// determing the pixel color on the screen. It determines if a ray intersects with 
// an object and finds the earliest time a ray intersects with an object.
class RayTracer {
public:
	// Generic constructor
	RayTracer();

	// Determines the pixel color that a ray should be intersecting with the list of object.
	RGBApixel shade(Ray&, Objects**, Light** light, int size, int numLights, bool toon);

	void setDepth(int newDepth);

private:
	// Helper function that finds the earliest hit a ray has with a list of objects
	hitInfo getFirstHit(Ray&, Objects**, int);

	RGBApercentage shadeHelper(Ray&, Objects**, Light** light, int size, int numLights, int recursionLevel, bool toon);

	int depth;
	double hit;		// Keeps track of current hit from ray
	hitInfo hitI;	// Struct holding info about a hit
};