#pragma once

#include "Objects.h"

// Represents a sphere that is a subclass of the object type. This
// has a radius along with coordinates for where the sphere is located
// and it also contains a color. Class is responsible for calculating when
// a ray hits it
class Sphere : public Objects {
public:
	// Sphere constructor
	Sphere(double r, double xCord, double yCord, double zCord, RGBApixel &col, RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, double shiny);

	// Copy constructor
	Sphere(const Sphere&);

	// Returns the time that a ray intersects with the sphere, -1 if no intersection
	double hit(Ray &ray) override;

private:
	double radius;	// Radius
	double A, B, C, discriminant;	// Info for the sphere. Used to reduce memory allocation during runtime
};