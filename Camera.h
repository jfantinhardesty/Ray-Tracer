#pragma once

#include <windows.h>
#include <GL/glut.h>
#include "Matrix.h"
#include "Objects.h"
#include "RayTracer.h"

class Camera {
private:
	RayTracer tracer;		// Ray tracer to be used in camera when rayTracing
	Ray ray;		// Ray used in ray tracer
	Point eye, look;
	Vector u, v, n, up;
	double H, W, viewAngle, aspect, nearDist, farDist;
	void setModelViewMatrix();

public:
	Camera() {}
	void set(double, double, double, double, double, double, double, double, double);
	void set(Point& eye, Point& look, Vector& up);
	void roll(double theta);
	void pitch(double theta);
	void yaw(double theta);
	void FocusedPitch(double theta);
	void FocusedYaw(double theta);
	void CenterFocus();
	void slide(double delU, double delV, double delN);
	void setShape(double vAng, double asp, double nearD, double farD);
	RGBApixel** rayTrace(int numRows, int numCols, int blockSize, Objects **obj, Light** light, int sizeObj, int lightSize, int depth, bool toon);
};