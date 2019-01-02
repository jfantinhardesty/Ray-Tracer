
#include <gl/glut.h>

#include "Camera.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Light.h"

using namespace std;

// globals for the pixmap
RGBApixel **pixmap2d;

// width and height of screen
int width, height, blockSize;

// Array of pointers to objects
Objects *obj[3];

// Array of pointers to light objects
Light *lights[4];

int sizeObj, numLights;

// Camera object
Camera camera;

// Keeps track of the rayTrace depth
int rayTraceDepth;

bool toon;

// 640 by 480 camera 

//
// drawing callback routine. Uncomment the line to draw the pixmap you want
//
void drawScreen() {
	glRasterPos2i(0, 0);

	//draw pixmap here
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);

	glFlush();
}

// Creates the objects for the scenes
void createObjects() {
	sizeObj = 3;
	RGBApixel color = { 255, 0, 0, 255 };
	RGBApercentage ambient = { 0.95f, 0.3f, 0.3f, 1.0f };
	RGBApercentage diffuse = { 0.95f, 0.3f, 0.3f, 1.0f };
	RGBApercentage specular = { 0.59f, 0.3f, 0.3f, 1.0f };
	obj[0] = new Sphere(.125, .125, -.25, -1, color, ambient, diffuse, specular, 3.0);

	color = { 0, 0, 255, 255 };
	ambient = { 0.7f, 0.7f, 0.7f, 1.0f };
	diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	specular = { 0.001f, 0.001f, 0.001f, 1.0f };
	obj[1] = new Sphere(.375, .5, .5, -1.75, color, ambient, diffuse, specular, 1.0);

	color = { 0, 255, 0, 255 };
	ambient = { 0.4f, 0.4f, 0.8f, 1.0f };
	diffuse = { 0.4f, 0.4f, 0.8f, 1.0f };
	specular = { 0.4f, 0.4f, 0.8f, 1.0f };
	obj[2] = new Sphere(.75, -.5, 0, -2.5, color, ambient, diffuse, specular, 89.6);
}

void createLights() {
	numLights = 4;

	RGBApercentage noAmbient = { 0,0,0,1 };
	RGBApercentage noDiffuse = { 0,0,0,1 };
	RGBApercentage noSpecular = { 0,0,0,1 };

	RGBApercentage ambient = { .4, .4, .4, 1 };

	// Global light
	lights[0] = new Light(ambient);

	// Point light
	ambient = { .65, .65, .65, 1 };
	RGBApercentage diffuse = { .65, .65, .65, 1 };
	Point point = Point(200, 100, 50);
	lights[1] = new Light(ambient, diffuse, noSpecular, point);

	// Spotlight
	RGBApercentage specular = { .4, .4, .7, 1 };
	point = Point(-1,0,1);
	Vector direction = Vector(0, 0, -1);
	lights[2] = new Light(noAmbient, noDiffuse, specular, .5, 30.0, point, direction);

	//Directional light
	diffuse = { .8, .8, .6, 1 };
	direction = Vector(-400, 692, 0);
	lights[3] = new Light(noAmbient, diffuse, noSpecular, direction);
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int width, int height) {
	// open window and establish coordinate system on it
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Ray Tracer");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION); //set projection to 2D
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
}

// Registers the key clicks for changing the blocksize
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		blockSize = 1;
		break;
	case '2':
		blockSize = 2;
		break;
	case '3':
		blockSize = 4;
		break;
	case '4':
		blockSize = 8;
		break;
	case '+':
		rayTraceDepth++;
		cout << rayTraceDepth << endl;
		break;
	case '-':
		if (rayTraceDepth > 1) {
			rayTraceDepth--;
		}
		break;
	case 't':
		toon = true;
		break;
	case 'p':
		toon = false;
		break;
	}
	cout << key;
	// RayTrace the scene
	pixmap2d = camera.rayTrace(height, width, blockSize, obj, lights, sizeObj, numLights, rayTraceDepth, toon);
	glutPostRedisplay();
}


int main() {
	width = 640;
	height = 480;
	blockSize = 2;
	rayTraceDepth = 3;
	toon = true;

	// Set the angle, aspect ratio, and near and far plane for the scene.
	// This is only used in the ray tracing algorithm to figure out information
	// and not used to draw the scene as that is done with a pixmap.
	camera.setShape(30.0, (double) width / height, 1, 10);

	// Set the eye, lookat and up information
	camera.set(0, 0, 1, 0, 0, -1, 0, 1, 0);

	// Create all of the objects to be used in the scene
	createObjects();

	createLights();

	// RayTrace the scene
	pixmap2d = camera.rayTrace(height, width, blockSize, obj, lights, sizeObj, numLights, rayTraceDepth, toon);

	// open window and establish coordinate system on it
	startgraphics(width, height);

	// register display callback routines
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawScreen);
	glutMainLoop();

	return 0;
}