#pragma once

#include "Matrix.h"

// The Ray class represents a ray in our ray tracing algorithm. It contains
// a starting point and then a direction
class Ray {
public:
	Point start;	// Starting point
	Vector dir;		// Direction of the ray

	// Constructor for the ray
	Ray();

	// Creates an inverse ray based on the matrix and starting ray
	Ray(Matrix, Ray&);

	// Sets the start point of the ray
	void setStart(Point&);

	// Sets the direction of the ray
	void setDirection(Vector&);
};