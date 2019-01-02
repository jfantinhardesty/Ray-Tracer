
#include "Sphere.h"

// Sphere constructor
Sphere::Sphere(double r, double xCord, double yCord, double zCord, RGBApixel &col, RGBApercentage &amb, RGBApercentage &dif, RGBApercentage &spec, double shiny) {
	x = xCord;
	y = yCord;
	z = zCord;
	color = col;
	ambient = amb;
	diffuse = dif;
	specular = spec;
	shinyness = shiny;
	radius = r;

	// Create the matrix transformed by the translation of the sphere and scaling of
	// sphere based on a sphere with a radius of 1.
	Transform trans;
	trans.matrix = matrix;
	trans.Translate(xCord, yCord, zCord);
	trans.Scale(radius , radius, radius);
	matrix = trans.matrix;
}

// Copy constructor
Sphere::Sphere(const Sphere &s) {
	x = s.x;
	y = s.y;
	z = s.z;
	color = s.color;
	radius = s.radius;
	matrix = s.matrix;
}

// Returns the time of the first hit of a ray against an object. -1 if no hit found
double Sphere::hit(Ray &ray) {
	Ray inverseRay(matrix, ray);

	// Calculate A,B,C in the quadratic formula
	A = inverseRay.dir.dot(inverseRay.dir);
	B = (inverseRay.dir).dot(inverseRay.start);
	C = inverseRay.start * inverseRay.start - 1;

	discriminant = B * B - A * C;

	// If discriminant is negative then no solutions
	if (discriminant < 0.0) {
		return -1;
	}
	double root = sqrt(discriminant);
	double time1 = (- B - root) / A;		// First hit
	double time2 = (- B + root) / A;		// Second hit

	// If time1 < time2 then time1 hit first
	if (time1 < time2) {
		return time1;
	}
	else {
		return time2;
	}
}
