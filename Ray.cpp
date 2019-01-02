
#include "Ray.h"

// Generic constructor that does nothing
Ray::Ray() {}

// Creates an inverse ray based on the matrix and starting ray
Ray::Ray(Matrix matrix, Ray &ray) {
	start.set2(matrix.Inverse() * ray.start);	// Find the start of the inverse ray
	dir.setAlt(matrix.Inverse() * ray.dir);		// Find the direction of the inverse ray
}

// Sets the starting point of the ray
void Ray::setStart(Point &p) {
	start.set(p);
}

// Sets the direction of the ray
void Ray::setDirection(Vector &v) {
	dir.set(v);
}