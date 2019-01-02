#pragma once

#include <iostream>
#include <sstream>
#include <math.h>

class Point;
class Vector;
class Matrix;

double const pi = 3.141592653f;

//3D points
class Point {

public:
	double x;
	double y;
	double z;
	double h;
	Point();
	Point(const Point&);
	Point(double, double, double);
	void set(Point&);
	void set2(Point);
	void set(double, double, double);
	double magnitude();

	Vector operator-(const Point&);
	double operator*(const Point&);
	Point operator+(const Vector&);

	void Print();
};


//3D vectors
class Vector {

public:
	double x;
	double y;
	double z;
	double h;
	Vector();
	Vector(const Vector&);
	Vector(double, double, double);
	void set(Vector&);
	void setAlt(Vector);
	void set(double, double, double);
	double dot(Vector&);
	double dot(Point&);
	Vector cross(Vector&);
	Vector cross(Point&);
	void normalize();
	double magnitude();

	Vector operator+(Vector&);
	Vector operator-(Vector&);
	Vector operator*(double);
	Vector newell(Point[3]);
	void Print();
};


//Matrices
class Matrix {

public:
	/*
	matrix array representation:
	[0 4 8  12]
	[1 5 9  13]
	[2 6 10 14]
	[3 7 11 15]
	*/
	double m[16];
	Matrix();

	double Determinant();
	Matrix Inverse();

	void Print(int);
	void Print();

	Point operator*(Point&);// 3DPoint = matrix * 3Dpoint;
	Vector operator*(Vector&);// 3Dvector = matrix * 3Dvector;
	Matrix operator*(Matrix&);// matrix = matrix * matrix;
	Matrix operator*(double);//matrix = matrix * double;

	void operator=(Matrix);//set matrix from matrix
	void operator=(double*);//set matrix from array

	void SetToIdentity();//set matrix to identity matrix
};


//Transformations
class Transform {

public:
	Matrix matrix;
	void Translate(double, double);//2D translate
	void Translate(double, double, double);//3Dtranslate

	void Rotate(double);//rotate around z axis
	void Rotate(double, double, double, double);//3D rotate

	void Scale(double, double);//2D scale
	void Scale(double, double, double);//3D scale

	void Shear(double, double);//2D Shear
	void Shear(double, double, double);//3D shear
};