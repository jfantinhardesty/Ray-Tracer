#include "Matrix.h"

void PrintNumber(double& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}

void PrintNumber(int& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}

void PrintNumber(long& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


Point::Point() {
	x = 0;
	y = 0;
	z = 0;
	h = 1;
}


Point::Point(const Point& p) {
	x = p.x;
	y = p.y;
	z = p.z;
	h = 1;
}


Point::Point(double i, double j, double k) {
	x = i;
	y = j;
	z = k;
	h = 1;
}

void Point::set(Point& p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

void Point::set2(Point p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

void Point::set(double i, double j, double k) {
	x = i;
	y = j;
	z = k;
}

double Point::magnitude() {
	return x * y * z;
}

Vector Point::operator-(const Point& p) {
	Vector r;
	r.x = x - p.x;
	r.y = y - p.y;
	r.z = z - p.z;
	return r;
}

double Point::operator*(const Point& p) {
	return x * p.x + y * p.y + z * p.z;
}

Point Point::operator+(const Vector& v) {
	Point r;
	r.x = x + v.x;
	r.y = y + v.y;
	r.z = z + v.z;
	return r;
}

void Point::Print() {
	printf("(");
	PrintNumber(x);
	printf(", ");
	PrintNumber(y);
	printf(", ");
	PrintNumber(z);
	printf(")\n");
}

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
	h = 0;
}

Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	h = 0;
}

Vector::Vector(double i, double j, double k) {
	x = i;
	y = j;
	z = k;
	h = 0;
}

void Vector::set(Vector& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void Vector::setAlt(Vector vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void Vector::set(double i, double j, double k) {
	x = i;
	y = j;
	z = k;
}

double Vector::dot(Vector& vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}

double Vector::dot(Point& pnt) {
	return x * pnt.x + y * pnt.y + z * pnt.z;
}

Vector Vector::cross(Vector& vec) {
	Vector r;

	r.x = y * vec.z - z * vec.y;
	r.y = z * vec.x - x * vec.z;
	r.z = x * vec.y - y * vec.x;
	return r;
}

Vector Vector::cross(Point& pnt) {
	Vector r;

	r.x = y * pnt.z - z * pnt.y;
	r.y = z * pnt.x - x * pnt.z;
	r.z = x * pnt.y - y * pnt.x;
	return r;
}

Vector Vector::newell(Point pnt[3]) {
	Vector r;
	r.x = 0;
	r.y = 0;
	r.z = 0;
	int next = 0;
	for (int i = 0; i < 3; i++) {
		next = i + 1;
		if (next > 2) {
			next = 0;
		}
		r.x += (pnt[i].y - pnt[next].y)*(pnt[i].z + pnt[next].z);
		r.y += (pnt[i].z - pnt[next].z)*(pnt[i].x + pnt[next].x);
		r.z += (pnt[i].x - pnt[next].x)*(pnt[i].y + pnt[next].y);

	}

	return r;
}

void Vector::normalize() {
	double d;
	//d = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	d = magnitude();
	x /= d;
	y /= d;
	z /= d;
}

double Vector::magnitude() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::operator+(Vector& v) {
	Vector r;
	r.set(x + v.x, y + v.y, z + v.z);
	return r;
}


Vector Vector::operator-(Vector& v) {
	Vector r;
	r.set(x - v.x, y - v.y, z - v.z);
	return r;
}


//void Vector::operator=(const Vector& v) {
//	set(x - v.x, y - v.y, z - v.z);
//}


Vector Vector::operator*(double s) {
	Vector r;
	r.set(x * s, y * s, z * s);
	return r;
}

void Vector::Print() {
	printf("<");
	PrintNumber(x);
	printf(", ");
	PrintNumber(y);
	printf(", ");
	PrintNumber(z);
	printf(">\n");
}


Matrix::Matrix() {
	SetToIdentity();
}


void Matrix::SetToIdentity() {
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

Point Matrix::operator*(Point& point) {
	Point r;

	r.x = point.x*m[0] + point.y*m[4] + point.z*m[8] + point.h*m[12];
	r.y = point.x*m[1] + point.y*m[5] + point.z*m[9] + point.h*m[13];
	r.z = point.x*m[2] + point.y*m[6] + point.z*m[10] + point.h*m[14];
	r.h = point.x*m[3] + point.y*m[7] + point.z*m[11] + point.h*m[15];

	return r;
}


Vector Matrix::operator*(Vector& vec) {
	Vector r;

	r.x = vec.x*m[0] + vec.y*m[4] + vec.z*m[8] + vec.h*m[12];
	r.y = vec.x*m[1] + vec.y*m[5] + vec.z*m[9] + vec.h*m[13];
	r.z = vec.x*m[2] + vec.y*m[6] + vec.z*m[10] + vec.h*m[14];
	r.h = vec.x*m[3] + vec.y*m[7] + vec.z*m[11] + vec.h*m[15];

	return r;
}


Matrix Matrix::operator*(Matrix& mat) {
	Matrix r;
	r.m[0] = m[0] * mat.m[0] + m[4] * mat.m[1] + m[8] * mat.m[2] + m[12] * mat.m[3];
	r.m[1] = m[1] * mat.m[0] + m[5] * mat.m[1] + m[9] * mat.m[2] + m[13] * mat.m[3];
	r.m[2] = m[2] * mat.m[0] + m[6] * mat.m[1] + m[10] * mat.m[2] + m[14] * mat.m[3];
	r.m[3] = m[3] * mat.m[0] + m[7] * mat.m[1] + m[11] * mat.m[2] + m[15] * mat.m[3];
	r.m[4] = m[0] * mat.m[4] + m[4] * mat.m[5] + m[8] * mat.m[6] + m[12] * mat.m[7];
	r.m[5] = m[1] * mat.m[4] + m[5] * mat.m[5] + m[9] * mat.m[6] + m[13] * mat.m[7];
	r.m[6] = m[2] * mat.m[4] + m[6] * mat.m[5] + m[10] * mat.m[6] + m[14] * mat.m[7];
	r.m[7] = m[3] * mat.m[4] + m[7] * mat.m[5] + m[11] * mat.m[6] + m[15] * mat.m[7];
	r.m[8] = m[0] * mat.m[8] + m[4] * mat.m[9] + m[8] * mat.m[10] + m[12] * mat.m[11];
	r.m[9] = m[1] * mat.m[8] + m[5] * mat.m[9] + m[9] * mat.m[10] + m[13] * mat.m[11];
	r.m[10] = m[2] * mat.m[8] + m[6] * mat.m[9] + m[10] * mat.m[10] + m[14] * mat.m[11];
	r.m[11] = m[3] * mat.m[8] + m[7] * mat.m[9] + m[11] * mat.m[10] + m[15] * mat.m[11];
	r.m[12] = m[0] * mat.m[12] + m[4] * mat.m[13] + m[8] * mat.m[14] + m[12] * mat.m[15];
	r.m[13] = m[1] * mat.m[12] + m[5] * mat.m[13] + m[9] * mat.m[14] + m[13] * mat.m[15];
	r.m[14] = m[2] * mat.m[12] + m[6] * mat.m[13] + m[10] * mat.m[14] + m[14] * mat.m[15];
	r.m[15] = m[3] * mat.m[12] + m[7] * mat.m[13] + m[11] * mat.m[14] + m[15] * mat.m[15];

	return r;
}

Matrix Matrix::operator *(double s) {
	Matrix mat;
	int i;

	for (i = 0; i < 16; ++i) {
		mat.m[i] = m[i] * s;
	}
	return mat;
}


void Matrix::operator=(Matrix mat) {
	m[0] = mat.m[0];
	m[1] = mat.m[1];
	m[2] = mat.m[2];
	m[3] = mat.m[3];
	m[4] = mat.m[4];
	m[5] = mat.m[5];
	m[6] = mat.m[6];
	m[7] = mat.m[7];
	m[8] = mat.m[8];
	m[9] = mat.m[9];
	m[10] = mat.m[10];
	m[11] = mat.m[11];
	m[12] = mat.m[12];
	m[13] = mat.m[13];
	m[14] = mat.m[14];
	m[15] = mat.m[15];
}


void Matrix::operator=(double* mat) {
	m[0] = mat[0];
	m[1] = mat[1];
	m[2] = mat[2];
	m[3] = mat[3];
	m[4] = mat[4];
	m[5] = mat[5];
	m[6] = mat[6];
	m[7] = mat[7];
	m[8] = mat[8];
	m[9] = mat[9];
	m[10] = mat[10];
	m[11] = mat[11];
	m[12] = mat[12];
	m[13] = mat[13];
	m[14] = mat[14];
	m[15] = mat[15];
}

void Transform::Translate(double x, double y) {
	Matrix mat;
	mat.m[9] = y;
	mat.m[8] = x;
	matrix = matrix * mat;
}


void Transform::Translate(double x, double y, double z) {
	Matrix mat;
	mat.m[14] = z;
	mat.m[13] = y;
	mat.m[12] = x;
	matrix = matrix * mat;
}


void Transform::Rotate(double degrees) {
	Matrix mat;
	double c, s;
	static double const pi = 3.141592653f;
	degrees = degrees * pi / 180;
	c = cos(degrees);
	s = sin(degrees);

	mat.m[0] = c;
	mat.m[1] = s;
	mat.m[4] = -1 * s;
	mat.m[5] = c;

	matrix = matrix * mat;

}


void Transform::Rotate(double degrees, double vx, double vy, double vz) {
	Matrix mat;
	double x, y, z, ic, c, s, d;
	static double const pi = 3.141592653f;

	vx = pow(vx, 2.0f);
	vy = pow(vy, 2.0f);
	vz = pow(vz, 2.0f);
	d = vx + vy + vz;
	if (d > 0) {
		vx /= d;
		vy /= d;
		vz /= d;
		x = sqrt(vx);
		y = sqrt(vy);
		z = sqrt(vz);

		degrees = degrees * pi / 180;
		c = cos(degrees);
		s = sin(degrees);
		ic = 1 - c;

		mat.m[0] = vx + (1 - vx)*c;
		mat.m[1] = x * y*ic + z * s;
		mat.m[2] = x * z*ic - y * s;
		mat.m[3] = 0;
		mat.m[4] = x * y*ic - z * s;
		mat.m[5] = vy + (1 - vy)*c;
		mat.m[6] = y * z*ic + x * s;
		mat.m[7] = 0;
		mat.m[8] = x * z*ic + y * s;
		mat.m[9] = y * z*ic - x * s;
		mat.m[10] = vz + (1 - vz)*c;
		mat.m[11] = 0;
		mat.m[12] = 0;
		mat.m[13] = 0;
		mat.m[14] = 0;
		mat.m[15] = 1;

		matrix = matrix * mat;
	}
}


void Transform::Scale(double x, double y) {
	Matrix mat;
	mat.m[0] = x;
	mat.m[5] = y;
	matrix = matrix * mat;
}


void Transform::Scale(double x, double y, double z) {
	Matrix mat;
	mat.m[0] = x;
	mat.m[5] = y;
	mat.m[10] = z;
	matrix = matrix * mat;
}


void Transform::Shear(double x, double y) {
	Matrix mat;
	mat.m[4] = x;
	mat.m[1] = y;
	matrix = matrix * mat;
}


void Transform::Shear(double x, double y, double z) {
	Matrix mat;
	mat.m[1] = y;
	mat.m[2] = x;
	mat.m[4] = x;
	mat.m[6] = y;
	mat.m[8] = z;
	mat.m[9] = z;
	matrix = matrix * mat;
}


Matrix Matrix::Inverse() {
	Matrix mat;
	mat.m[0] = m[9] * m[14] * m[11] - m[13] * m[10] * m[11] + m[13] * m[6] * m[11] - m[5] * m[14] * m[11] - m[9] * m[6] * m[15] + m[5] * m[10] * m[15];
	mat.m[4] = m[12] * m[10] * m[11] - m[8] * m[14] * m[11] - m[12] * m[6] * m[11] + m[4] * m[14] * m[11] + m[8] * m[6] * m[15] - m[4] * m[10] * m[15];
	mat.m[8] = m[8] * m[13] * m[11] - m[12] * m[9] * m[11] + m[12] * m[5] * m[11] - m[4] * m[13] * m[11] - m[8] * m[5] * m[15] + m[4] * m[9] * m[15];
	mat.m[12] = m[12] * m[9] * m[6] - m[8] * m[13] * m[6] - m[12] * m[5] * m[10] + m[4] * m[13] * m[10] + m[8] * m[5] * m[14] - m[4] * m[9] * m[14];
	mat.m[1] = m[13] * m[10] * m[3] - m[9] * m[14] * m[3] - m[13] * m[2] * m[11] + m[1] * m[14] * m[11] + m[9] * m[2] * m[15] - m[1] * m[10] * m[15];
	mat.m[5] = m[8] * m[14] * m[3] - m[12] * m[10] * m[3] + m[12] * m[2] * m[11] - m[0] * m[14] * m[11] - m[8] * m[2] * m[15] + m[0] * m[10] * m[15];
	mat.m[9] = m[12] * m[9] * m[3] - m[8] * m[13] * m[3] - m[12] * m[1] * m[11] + m[0] * m[13] * m[11] + m[8] * m[1] * m[15] - m[0] * m[9] * m[15];
	mat.m[13] = m[8] * m[13] * m[2] - m[12] * m[9] * m[2] + m[12] * m[1] * m[10] - m[0] * m[13] * m[10] - m[8] * m[1] * m[14] + m[0] * m[9] * m[14];
	mat.m[2] = m[5] * m[14] * m[3] - m[13] * m[6] * m[3] + m[13] * m[2] * m[11] - m[1] * m[14] * m[11] - m[5] * m[2] * m[15] + m[1] * m[6] * m[15];
	mat.m[6] = m[12] * m[6] * m[3] - m[4] * m[14] * m[3] - m[12] * m[2] * m[11] + m[0] * m[14] * m[11] + m[4] * m[2] * m[15] - m[0] * m[6] * m[15];
	mat.m[10] = m[4] * m[13] * m[3] - m[12] * m[5] * m[3] + m[12] * m[1] * m[11] - m[0] * m[13] * m[11] - m[4] * m[1] * m[15] + m[0] * m[5] * m[15];
	mat.m[14] = m[12] * m[5] * m[2] - m[4] * m[13] * m[2] - m[12] * m[1] * m[6] + m[0] * m[13] * m[6] + m[4] * m[1] * m[14] - m[0] * m[5] * m[14];
	mat.m[3] = m[9] * m[6] * m[3] - m[5] * m[10] * m[3] - m[9] * m[2] * m[11] + m[1] * m[10] * m[11] + m[5] * m[2] * m[11] - m[1] * m[6] * m[11];
	mat.m[7] = m[4] * m[10] * m[3] - m[8] * m[6] * m[3] + m[8] * m[2] * m[11] - m[0] * m[10] * m[11] - m[4] * m[2] * m[11] + m[0] * m[6] * m[11];
	mat.m[11] = m[8] * m[5] * m[3] - m[4] * m[9] * m[3] - m[8] * m[1] * m[11] + m[0] * m[9] * m[11] + m[4] * m[1] * m[11] - m[0] * m[5] * m[11];
	mat.m[15] = m[4] * m[9] * m[2] - m[8] * m[5] * m[2] + m[8] * m[1] * m[6] - m[0] * m[9] * m[6] - m[4] * m[1] * m[10] + m[0] * m[5] * m[10];
	return mat * (1 / Determinant());
}

void Matrix::Print(int i) {
	std::ostringstream oss;
	oss << m[i];
	std::string s(oss.str());
	std::cout << s;
}

void Matrix::Print() {
	printf("[");
	Print(0);
	printf(" ");
	Print(4);
	printf(" ");
	Print(8);
	printf(" ");
	Print(12);
	printf("]\n[");
	Print(1);
	printf(" ");
	Print(5);
	printf(" ");
	Print(9);
	printf(" ");
	Print(13);
	printf("]\n[");
	Print(2);
	printf(" ");
	Print(6);
	printf(" ");
	Print(10);
	printf(" ");
	Print(14);
	printf("]\n[");
	Print(3);
	printf(" ");
	Print(7);
	printf(" ");
	Print(11);
	printf(" ");
	Print(15);
	printf("]\n");
}

double Matrix::Determinant() {
	return m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] - m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
		m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] - m[12] * m[9] * m[2] * m[11] + m[8] * m[13] * m[2] * m[11] +
		m[12] * m[1] * m[10] * m[11] - m[0] * m[13] * m[10] * m[11] - m[8] * m[1] * m[14] * m[11] + m[0] * m[9] * m[14] * m[11] +
		m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] - m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
		m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] - m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
		m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] - m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
}