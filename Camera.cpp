
#include "Camera.h"

// setModelViewMatrix used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::setModelViewMatrix() {
	double m[16];
	Vector eVec(eye.x, eye.y, eye.z);

	m[0] = u.x;
	m[1] = v.x;
	m[2] = n.x;
	m[3] = 0;
	m[4] = u.y;
	m[5] = v.y;
	m[6] = n.y;
	m[7] = 0;
	m[8] = u.z;
	m[9] = v.z;
	m[10] = n.z;
	m[11] = 0;
	m[12] = -eVec.dot(u);
	m[13] = -eVec.dot(v);
	m[14] = -eVec.dot(n);
	m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);
}

void Camera::set(double ex, double ey, double ez, double lx, double ly, double lz, double ux, double uy, double uz) {
	Point e(ex, ey, ez);
	Point l(lx, ly, lz);
	Vector y(ux, uy, uz);
	set(e, l, y);
}

// set used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::set(Point& e, Point& l, Vector& y) {
	eye.set(e);
	look.set(l);
	up.set(y);
	Vector vec;
	vec = e - l;
	n.setAlt(vec);
	vec = y.cross(n);
	u.setAlt(vec);
	n.normalize();
	u.normalize();
	vec = n.cross(u);
	v.setAlt(vec);
	v.normalize();
	setModelViewMatrix();

	// Set the start location for the ray
	ray.setStart(eye);
}

// slide used in the book "Computer Graphics using OpenGL" Hill/Kelley page 337
// the book had typos that have been corrected here
// move camera and look point according to delta values
void Camera::slide(double delU, double delV, double delN) {
	double dx = delU * u.x + delV * v.x + delN * n.x;
	double dy = delU * u.y + delV * v.y + delN * n.y;
	double dz = delU * u.z + delV * v.z + delN * n.z;

	eye.x += dx;
	eye.y += dy;
	eye.z += dz;

	look.x += dx;
	look.y += dy;
	look.z += dz;

	setModelViewMatrix();
}

//Change camera to perspective or parallel
void Camera::setShape(double vAng, double asp, double nearD, double farD) {
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;

	H = nearDist * tan(((viewAngle / 2)*pi) / 180);
	W = H * aspect;
}

// roll used in the book "Computer Graphics using OpenGL" Hill/Kelley page 338
// rotate around n vector
void Camera::roll(double theta) {
	double cs = cos(pi / 180 * theta);
	double sn = sin(pi / 180 * theta);
	Vector t(u);
	u.set(cs*t.x + sn * v.x, cs*t.y + sn * v.y, cs*t.z + sn * v.z);
	v.set(-sn * t.x + cs * v.x, -sn * t.y + cs * v.y, -sn * t.z + cs * v.z);
	u.normalize();
	v.normalize();
	setModelViewMatrix();
}

// rotate camera around u vector
void Camera::pitch(double theta) {
	double cs = cos(pi / 180 * theta);
	double sn = sin(pi / 180 * theta);
	Vector t(v);
	v.set(cs*t.x + sn * n.x, cs*t.y + sn * n.y, cs*t.z + sn * n.z);
	n.set(-sn * t.x + cs * n.x, -sn * t.y + cs * n.y, -sn * t.z + cs * n.z);
	v.normalize();
	n.normalize();
	setModelViewMatrix();
}

//rotate camera around v vector
void Camera::yaw(double theta) {
	double cs = cos(pi / 180 * theta);
	double sn = sin(pi / 180 * theta);
	Vector t(n);
	n.set(cs*t.x - sn * u.x, cs*t.y - sn * u.y, cs*t.z - sn * u.z);
	u.set(sn * t.x + cs * u.x, sn * t.y + cs * u.y, sn * t.z + cs * u.z);
	n.normalize();
	u.normalize();
	setModelViewMatrix();
}

// rotate camera around a fixed point such that the camera
// is always looking at that point (0, 0, 0);
void Camera::FocusedPitch(double theta) {
	//to be completed
}

// rotate camera around a fixed point such that the camera
// is always looking at that point (0, 0, 0);
void Camera::FocusedYaw(double theta) {
	//to be completed
}

void Camera::CenterFocus() {
	Point center;
	set(eye, center, up);
}

// Ray traces the scene using the ray trace algorithm
RGBApixel** Camera::rayTrace(int numRows, int numCols, int blockSize, Objects **obj, Light** light, int sizeObj, int lightSize, int depth, bool toon) {
	int row, col;
	Vector temp1, temp2, direction;
	RGBApixel color;

	tracer.setDepth(depth);

	// Allocate a RGBA pixmap organized as a 2D array
	RGBApixel **pixmap2d = new RGBApixel*[numRows];
	pixmap2d[0] = new RGBApixel[numRows * numCols];
	for (row = 1; row < numRows; row++) {
		pixmap2d[row] = pixmap2d[row - 1] + numCols;
	}

	// Iterate through the pixmap to ccompute the color
	for (row = 0; row < numRows; row += blockSize) {
		for (col = 0; col < numCols; col += blockSize) {
			// Finds the direction of the Ray
			temp1 = u * (-W + W * ((2 * col) / (double)numCols));
			temp2 = v * (-H + H * ((2 * row) / (double)numRows));
			direction = n * (-1 * nearDist) + temp1 + temp2;

			ray.setDirection(direction);

			// Find the color value the pixel should be colored
			color = tracer.shade(ray, obj, light, sizeObj, lightSize, toon);

			// Set the other pixels in the pixmap that won't be computed from the blocksize
			for (int i = 0; i < blockSize; ++i) {
				for (int j = 0; j < blockSize; ++j) {
					pixmap2d[row + i][col + j] = color;
				}
			}
		}
	}

	// Add a darker gradient between different colors
	if (toon) {
		for (row = 0; row < numRows - blockSize; row += blockSize) {
			for (col = 0; col < numCols - blockSize; col += blockSize) {

				// We check for a change in color between pixels, if there is a change, we try to create a darker line between the two colors for toon model
				if (abs(pixmap2d[row][col].r - pixmap2d[row + blockSize][col + blockSize].r) > 3 || abs(pixmap2d[row][col].g - pixmap2d[row + blockSize][col + blockSize].g) > 3 || abs(pixmap2d[row][col].b - pixmap2d[row + blockSize][col + blockSize].b) > 3) {
					for (int i = 0; i < blockSize; ++i) {
						for (int j = 0; j < blockSize; ++j) {
							pixmap2d[row + i][col + j].r = .8 * pixmap2d[row][col].r;
							pixmap2d[row + i][col + j].g = .8 * pixmap2d[row][col].g;
							pixmap2d[row + i][col + j].b = .8 * pixmap2d[row][col].b;
						}
					}
				}
				if (abs(pixmap2d[row][col].r - pixmap2d[row + blockSize][col].r) > 3 || abs(pixmap2d[row][col].g - pixmap2d[row + blockSize][col].g) > 3 || abs(pixmap2d[row][col].b - pixmap2d[row + blockSize][col].b) > 3) {
					for (int i = 0; i < blockSize; ++i) {
						for (int j = 0; j < blockSize; ++j) {
							pixmap2d[row + i][col + j].r = .8 * pixmap2d[row][col].r;
							pixmap2d[row + i][col + j].g = .8 * pixmap2d[row][col].g;
							pixmap2d[row + i][col + j].b = .8 * pixmap2d[row][col].b;
						}
					}
				}
				else if (abs(pixmap2d[row][col].r - pixmap2d[row][col + blockSize].r) > 3 || abs(pixmap2d[row][col].g - pixmap2d[row][col + blockSize].g) > 3 || abs(pixmap2d[row][col].b - pixmap2d[row][col + blockSize].b) > 3) {
					for (int i = 0; i < blockSize; ++i) {
						for (int j = 0; j < blockSize; ++j) {
							pixmap2d[row + i][col + j].r = .8 * pixmap2d[row][col].r;
							pixmap2d[row + i][col + j].g = .8 * pixmap2d[row][col].g;
							pixmap2d[row + i][col + j].b = .8 * pixmap2d[row][col].b;
						}
					}
				}
			}
		}
	}

	return pixmap2d;
}