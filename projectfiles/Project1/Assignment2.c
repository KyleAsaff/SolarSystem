
/************************************************************************************

File: 			Assignment2.c

Description:	Builds a solar system
				
				****************************BONUS*****************************
				For my bonus the space ship will shoot purple lasers. 
				Press f1 to shoot a laser.
				The maximum amount of lasers at one time is set by MAX_LASERS.
				***************************************************************

Author:			Kyle Asaff

*************************************************************************************/


/* include the library header files */
#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>

#define ESC 27
#define MAX_LASERS 10
#define MAX_STARS 1000

/************************************************************************

Function:      Speed Variables

Description:    adjust these to change the speeds of the animations

*************************************************************************/

// The speed the space ship moves at
GLfloat speedCamera = 0.01*10;

// Adjust speed of orbit
GLfloat orbitSpeed = 0.8*10;

// The speed the lasers move at
float laserSpeed = 2*10;
/************************************************************************



*************************************************************************/

// Hold values from enterprise.txt
struct enterprise {
	GLfloat p1;
	GLfloat p2;
	GLfloat p3;
};

// Hold values for star positions
struct starTranslation {
	int x;
	int y;
	int z;
};

// Hold values for the lasers
struct laser {
	int shot;
	GLfloat distance;
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

// The maximum distance the lasers will appear at
float maxlaserDistance = 100.0;

// Create the structures for the enterprise, lasers, and stars
struct laser lasers[MAX_LASERS];
struct enterprise eVertex[1201];
struct enterprise eFace[1989];
struct starTranslation stars[MAX_STARS];

// The camera movement
GLfloat zMove = 0.0;
GLfloat xMove = 0.0;
GLfloat yMove = 0.0;

// Enabling and disabling functions
int enableOrbit = 0;
int enableCorona = 0;
int enableStars = 0;
int enableShield = 0;

// Thetas for axis (x, y, z)
static GLfloat theta[] = { 0.0, 0.0, 0.0 };

// Current camera position
GLfloat xCamera = 0.0;
GLfloat yCamera = 1.0;
GLfloat zCamera = -20.0;
GLfloat xlCamera = 0.0;
GLfloat ylCamera = 0.0;
GLfloat zlCamera = 0.0;

// window dimensions
GLint windowWidth = 1000;
GLint windowHeight = 800;

/************************************************************************

    Function:      randomNumber

    Description:    Generates a random float number between 0.0 and a given max

*************************************************************************/

float randomNumber(float max) {
    float x = ((float)rand()/(float)(RAND_MAX)) * max;
    return x;
}

/************************************************************************

Function:		planet

Description:	Draws a sphere

*************************************************************************/
void planet()
{

	GLfloat x, y, z, theta, phi;
	GLfloat c;
	x = y = 0;
	z = 1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	c = 3.14159 / 180.0;
	z = sin(c*80.0);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		x = sin(c*theta)*cos(c*80.0);
		y = cos(c*theta)*cos(c*80.0);
		glVertex3f(x, y, z);
	}
	glEnd();
	x = y = 0;
	z = -1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	z = -sin(c*80.0);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		x = sin(c*theta)*cos(c*80.0);
		y = cos(c*theta)*cos(c*80.0);
		glVertex3f(x, y, z);
	}
	glEnd();
	for (phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			x = sin(c*theta)*cos(c*phi);
			y = cos(c*theta)*cos(c*phi);
			z = sin(c*phi);
			glVertex3f(x, y, z);

			x = sin(c*theta)*cos(c*(phi + 20.0));
			y = cos(c*theta)*cos(c*(phi + 20.0));
			z = sin(c*(phi + 20.0));
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}
/************************************************************************

Function:		shield

Description:	Draws the ships shield with a sphere

*************************************************************************/
void shield()
{

	//use random gray colors to make the shield shimmer gray
	float randomcolor1;

	GLfloat x, y, z, theta, phi;
	GLfloat c;
	x = y = 0;
	z = 1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	c = 3.14159 / 180.0;
	z = sin(c*80.0);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		randomcolor1 = randomNumber(0.1)+0.5;
		glColor4f(randomcolor1, randomcolor1, randomcolor1, 0.07 + randomNumber(0.05));
		x = sin(c*theta)*cos(c*80.0);
		y = cos(c*theta)*cos(c*80.0);
		glVertex3f(x, y, z);
	}
	glEnd();
	x = y = 0;
	z = -1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	z = -sin(c*80.0);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		randomcolor1 = randomNumber(0.1)+0.5;
		glColor4f(randomcolor1, randomcolor1, randomcolor1, 0.07 + randomNumber(0.05));
		x = sin(c*theta)*cos(c*80.0);
		y = cos(c*theta)*cos(c*80.0);
		glVertex3f(x, y, z);
	}
	glEnd();
	for (phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			randomcolor1 = randomNumber(0.1)+0.5;
			glColor4f(randomcolor1, randomcolor1, randomcolor1, 0.07 + randomNumber(0.05));
			x = sin(c*theta)*cos(c*phi);
			y = cos(c*theta)*cos(c*phi);
			z = sin(c*phi);
			glVertex3f(x, y, z);

			x = sin(c*theta)*cos(c*(phi + 20.0));
			y = cos(c*theta)*cos(c*(phi + 20.0));
			z = sin(c*(phi + 20.0));
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

/************************************************************************

Function:		drawShield

Description:	Draws the shield at the enterprise's position

*************************************************************************/
void drawShield() {
	glPushMatrix();
	glTranslatef(0.0 + xlCamera, -0.6 + ylCamera, -15.5 + zlCamera);
	glScalef(0.5, 0.5, 0.7);
	shield();
	glPopMatrix();
}

/************************************************************************

Function:		drawOrbit

Description:	Handles drawing orbits with GL_LINES
*************************************************************************/
void drawOrbit() {
	GLfloat x, z;
	GLfloat radius = 1.0;
	int i = 0;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);

	x = radius * cos(359 * 3.14159 / 180.0);
	z = radius * sin(359 * 3.14159 / 180.0);
	for (i = 0; i < 360; i++)
	{
		glVertex3f(x, 0.0, z);
		x = (GLfloat)radius * cos(i * 3.14159 / 180.f);
		z = (GLfloat)radius * sin(i * 3.14159 / 180.0);
		glVertex3f(x, 0.0, z);
	}
	glEnd();
}

/************************************************************************

Function:		drawRing

Description:	Creates orbits for each planets using drawOrbit

*************************************************************************/
void drawRing() {
	// Draw Mercury orbit
	glPushMatrix();
	glScalef(2, 2, 2);
	drawOrbit();
	glPopMatrix();
	// Draw Venus orbit
	glPushMatrix();
	glScalef(3.5, 3.5, 3.5);
	drawOrbit();
	glPopMatrix();
	// Draw Earth orbit
	glPushMatrix();
	glScalef(4.5, 4.5, 4.5);
	drawOrbit();
	glPopMatrix();
	// Draw Moon orbit
	glPushMatrix();
	glRotatef(theta[1] * 27 * orbitSpeed, 0.0, 1.0, 0.0);
	glTranslatef(4.5, 0.0, 0.0);
	glScalef(0.55, 0.55, 0.55);
	drawOrbit();
	glPopMatrix();
	// Draw Mars orbit
	glPushMatrix();
	glScalef(5.5, 5.5, 5.5);
	drawOrbit();
	glPopMatrix();
	// Draw Jupiter orbit
	glPushMatrix();
	glScalef(7.5, 7.5, 7.5);
	drawOrbit();
	glPopMatrix();
	// Draw Saturn orbit
	glPushMatrix();
	glScalef(9.5, 9.5, 9.5);
	drawOrbit();
	glPopMatrix();
	// Draw Uranus orbit
	glPushMatrix();
	glScalef(10.5, 10.5, 10.5);
	drawOrbit();
	glPopMatrix();
	// Draw Uranus orbit
	glPushMatrix();
	glScalef(11.5, 11.5, 11.5);
	drawOrbit();
	glPopMatrix();
	// Draw Pluto orbit
	glPushMatrix();
	glScalef(13.5, 13.5, 13.5);
	drawOrbit();
	glPopMatrix();
}

/************************************************************************

Function:		drawPlanets

Description:	Handles drawing the planets and rotating the planets

*************************************************************************/
void drawPlanets() {
	
	// Draw Sun
	glColor3f(1, 1, 0);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	planet();
	glPopMatrix(); 

	// Draw Mercury
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 40 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(0.2, 0.2, 0.2);
	glColor3f(0.6, 0.627, 0.627);
	planet();
	glPopMatrix();

	// Draw Venus
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 35 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(3.5, 0.0, 0.0);
	glScalef(0.3, 0.3, 0.3);
	glColor3f(1, 1, 0.6);
	planet();
	glPopMatrix();

	// Draw Earth
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 27 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(4.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glColor3f(0.2, 0.6, 1.0);
	planet();
	glPopMatrix();

	// Draw Moon
	glPushMatrix();
	glRotatef(theta[1] * 27 * orbitSpeed, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(4.5, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef((theta[1] * 70 * orbitSpeed), 0.0, 1.0, 0.0);
	glTranslatef(-5.5, 0.0, 0.0);
	glColor3f(0.956, 0.956, 0.956);
	planet();
	glPopMatrix();
	glPopMatrix();

	// Draw Mars
	glColor3f(1, 0.0, 0.0);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 23 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(5.5, 0.0, 0.0);
	glScalef(0.3, 0.3, 0.3);
	planet();
	glPopMatrix();

	// Draw Jupiter
	glColor3f(1.0, 0.5, 0.0);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 17 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(7.5, 0.0, 0.0);
	glScalef(0.65, 0.65, 0.65);
	planet();
	glPopMatrix();

	// Draw Saturn
	glColor3f(1, 0.8, 0.6);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 14 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(9.5, 0.0, 0.0);
	glScalef(0.45, 0.45, 0.45);
	planet();
	glPopMatrix();

	// Draw Uranus
	glColor3f(0.4, 1.0, 0.698);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 9 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(10.5, 0.0, 0.0);
	glScalef(0.35, 0.35, 0.35);
	planet();
	glPopMatrix();

	// Draw Neptune
	glColor3f(0.4, 1.0, 1.0);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 5 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(11.5, 0.0, 0.0);
	glScalef(0.35, 0.35, 0.35);
	planet();
	glPopMatrix();

	// Draw Pluto
	glColor3f(0.376, 0.376, 0.376);
	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1] * 2 * orbitSpeed, 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(13.5, 0.0, 0.0);
	glScalef(0.15, 0.15, 0.15);
	planet();
	glPopMatrix();
}

/************************************************************************

Function:		generateStars

Description:	Generates Random Stars and stores their positions

*************************************************************************/
void generateStars() {
	int i = 0;
	for (i = 0; i < MAX_STARS; i++) {
		stars[i].x = (rand() % 1000) - 500;
		stars[i].y = (rand() % 1000) - 500;
		stars[i].z = (rand() % 1000) - 500;
	}
}

/************************************************************************

Function:		drawStars

Description:	Draw the randomly generated stars

*************************************************************************/
void drawStars() {
	int i = 0;
	for (i = 0; i < 500; i++) {
		// Show stars if stars turned on (this is so the orbits don't slow down due to more rendering)
		if (enableStars == 0)
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(randomNumber(1.0), randomNumber(1.0), randomNumber(1.0));
		glPushMatrix();
		glTranslatef(stars[i].x, stars[i].y, stars[i].z+500.0);
		glScalef(0.7, 0.7, 0.7);
		glPointSize(2.0);
		glBegin(GL_POINTS);
		glVertex3i(1, 1, 0);
		glEnd();
		glPopMatrix();
	}
}


/************************************************************************

Function:		drawCorona

Description:	Draws Sun Corona

*************************************************************************/
void drawCorona() {
	GLfloat x, y;
	GLfloat rad = 0.95;
	int i = 0;

	glLineWidth(2.5);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);

	x = rad * cos(359 * 3.14159 / 180.0);
	y = rad * sin(359 * 3.14159 / 180.0);
	for (i = 0; i < 360; i++) {
		if (rand() % 2 == 1) {
			glColor4f(1, 1, 0, 1.0);
			glVertex3f(x, y, 0.0);
			x = (GLfloat)rad * cos(i * 3.14159 / 180.0);
			y = (GLfloat)rad * sin(i * 3.14159 / 180.0);
			glColor4f(1, 0.6, 0.2, 0.1);
			glVertex3f(x*(1.9 - randomNumber(0.15)), y*(1.9 - randomNumber(0.15)), 0.0);
		}
	}
	glEnd();
	glLineWidth(1.0);
}

/************************************************************************

Function:		parseEnterprise

Description:	Handles parseing enterprise from enterprise.txt

*************************************************************************/
void parseEnterprise() {
	FILE *fp;
	char buff[128];
	int vCount = 0;
	int fCount = 0;

	fp = fopen("enterprise.txt", "r");

	if (fp == NULL)
		printf("Can't open file");
	else {
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			if (buff[0] == 'v') {
				sscanf(buff, "v %f %f %f", &eVertex[vCount].p1, &eVertex[vCount].p2, &eVertex[vCount].p3);
				vCount++;
			}
			if (buff[0] == 'f') {
				sscanf(buff, "f %f %f %f", &eFace[fCount].p1, &eFace[fCount].p2, &eFace[fCount].p3);
				fCount++;
			}
		}
	}
	fclose(fp);
}

/************************************************************************

Function:		drawEnterprise

Description:	Handles drawing the enterprise

*************************************************************************/

void drawEnterprise() {
	glPushMatrix();
	glTranslatef(0.0 + xlCamera, -0.6 + ylCamera, -15.5 + zlCamera);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glScalef(0.8, 0.8, 0.8);
	int i = 0;

	while (i < 1989) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.75, 0.75, 0.75);
		if (i < 1000 || i > 1950)
			glColor3f(0.37, 0.37, 0.37);
		glVertex3f(eVertex[(int)eFace[i].p1-1].p1, eVertex[(int)eFace[i].p1-1].p2, eVertex[(int)eFace[i].p1-1].p3);
		glVertex3f(eVertex[(int)eFace[i].p2 - 1].p1, eVertex[(int)eFace[i].p2 - 1].p2, eVertex[(int)eFace[i].p2 - 1].p3);
		glVertex3f(eVertex[(int)eFace[i].p3 - 1].p1, eVertex[(int)eFace[i].p3 - 1].p2, eVertex[(int)eFace[i].p3 - 1].p3);
		i++;
		glVertex3f(eVertex[(int)eFace[i].p1 - 1].p1, eVertex[(int)eFace[i].p1 - 1].p2, eVertex[(int)eFace[i].p1 - 1].p3);
		glVertex3f(eVertex[(int)eFace[i].p2 - 1].p1, eVertex[(int)eFace[i].p2 - 1].p2, eVertex[(int)eFace[i].p2 - 1].p3);
		glVertex3f(eVertex[(int)eFace[i].p3 - 1].p1, eVertex[(int)eFace[i].p3 - 1].p2, eVertex[(int)eFace[i].p3 - 1].p3);
		i++;
		glVertex3f(eVertex[(int)eFace[i].p1 - 1].p1, eVertex[(int)eFace[i].p1 - 1].p2, eVertex[(int)eFace[i].p1 - 1].p3);
		glVertex3f(eVertex[(int)eFace[i].p2 - 1].p1, eVertex[(int)eFace[i].p2 - 1].p2, eVertex[(int)eFace[i].p2 - 1].p3);
		glVertex3f(eVertex[(int)eFace[i].p3 - 1].p1, eVertex[(int)eFace[i].p3 - 1].p2, eVertex[(int)eFace[i].p3 - 1].p3);
		i++;
		glEnd();
	}
	glPopMatrix();
}


/************************************************************************

Function:      shootLaser

Description:    Shoots a laser from the ship

*************************************************************************/

void shootLaser() {
	int i = 0;
	for (i = 0; i < MAX_LASERS; i++) {
		if (lasers[i].shot == 1) {
			glColor3f(0.4, 0.0, 0.8);
			glPushMatrix();
			glTranslatef(lasers[i].x, lasers[i].y, lasers[i].z + lasers[i].distance);
			glScalef(0.05, 0.05, 0.5);
			planet();
			glPopMatrix();
		}
	}
}

/************************************************************************

Function:		myDisplay

Description:	Display callback, clears frame buffer and depth buffer,
positions the camera and draws the cube.

*************************************************************************/
void myDisplay(void)
{

	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix into the model view matrix
	glLoadIdentity();

	// set the camera position
	gluLookAt(xCamera, yCamera, zCamera,
		xlCamera, ylCamera, zlCamera,
		0, 1, 0);

	// draw the planets
	drawPlanets();

	// draw the planets orbits
	if (enableOrbit == 1)
		drawRing();

	// draw the sun's corona
	if (enableCorona == 1)
		drawCorona();

	// draw enterprise
	drawEnterprise();

	// draw the stars
	drawStars();

	shootLaser();

	// draw the enterprise shield
	if (enableShield == 1)
		drawShield();

	// swap the drawing buffers
	glutSwapBuffers();


}

/************************************************************************

Function:		myIdle

Description:	Updates the animation when idle.

*************************************************************************/
void myIdle()
{
	// Update the camera position
	if (xMove) {
		xCamera += xMove*speedCamera;
		xlCamera += xMove*speedCamera;
	}
	if (yMove) {
		yCamera += yMove*speedCamera;
		ylCamera += yMove*speedCamera;
	}
	if (zMove) {
		zCamera += zMove*speedCamera;
		zlCamera += zMove*speedCamera;
	}

	// Rotate planets around Y axis
	theta[1] += 0.01;

	// Reset theta (current orbit positions) so it doesn't go out of bounds of float
	if (theta[1] > 36000000.0) theta[1] -= 36000000;

	// Increases distance of a laser fired and resets at maxdistance
	int i;
	for (i = 0; i<MAX_LASERS; i++) {
		if (lasers[i].shot == 1)
			lasers[i].distance += 0.1*laserSpeed;
		if (lasers[i].distance > maxlaserDistance) {
			lasers[i].shot = 0.0;
			lasers[i].distance = 0.0;
		}
	}

	// Redraw the new state
	glutPostRedisplay();
}

/************************************************************************

Function:		normalKey, pressKey, releaseKey

Description:	User input callbacks

*************************************************************************/
void normalKey(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q')
		exit(0);

	if (key == 'r' && enableOrbit == 0 || key == 'R' && enableOrbit == 0)
		enableOrbit = 1;
	else if (key == 'r' && enableOrbit == 1 || key == 'R' && enableOrbit == 1)
		enableOrbit = 0;

	if (key == 'c' && enableCorona == 0 || key == 'C' && enableCorona == 0)
		enableCorona = 1;
	else if (key == 'c' && enableCorona == 1 || key == 'C' && enableCorona == 1)
		enableCorona = 0;

	if (key == 's' && enableStars == 0 || key == 'S' && enableStars == 0)
		enableStars = 1;
	else if (key == 's' && enableStars == 1 || key == 'S' && enableStars == 1)
		enableStars = 0;

	if (key == 'k' && enableShield == 0 || key == 'K' && enableShield == 0)
		enableShield = 1;
	else if (key == 'k' && enableShield == 1 || key == 'K' && enableShield == 1)
		enableShield = 0;

}


void pressKey(int key, int xx, int yy)
{
	int i;
	switch (key) {
	case GLUT_KEY_UP: yMove = 1.0; break;
	case GLUT_KEY_DOWN: yMove = -1.0; break;
	case GLUT_KEY_RIGHT: xMove = -1.0; break;
	case GLUT_KEY_LEFT: xMove = 1.0; break;
	case GLUT_KEY_PAGE_UP: zMove = 1.0; break;
	case GLUT_KEY_PAGE_DOWN: zMove = -1.0; break;
	case GLUT_KEY_F1:
		for (i = 0; i < MAX_LASERS; i++) {
			if (lasers[i].distance == 0.0) {
				lasers[i].shot = 1.0;
				lasers[i].x = 0.0 + xlCamera;
				lasers[i].y = -0.9 + ylCamera;
				lasers[i].z = -13.5 + zlCamera;
				break;
			}
		}
	}
}

void releaseKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: yMove = 0.0; break;
	case GLUT_KEY_DOWN: yMove = 0.0; break;
	case GLUT_KEY_RIGHT: xMove = 0.0; break;
	case GLUT_KEY_LEFT: xMove = 0.0; break;
	case GLUT_KEY_PAGE_UP: zMove = 0.0; break;
	case GLUT_KEY_PAGE_DOWN: zMove = 0.0; break;
	}
}




/************************************************************************

Function:		initializeGL

Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void)
{
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set background color to be black
	glClearColor(0, 0, 0, 1.0);

}


/************************************************************************

Function:		myResize

Description:	Handles a user resize of the window.

*************************************************************************/
void myResize(int newWidth, int newHeight)
{

	// Update the new width
	windowWidth = newWidth;
	// Update the new height
	windowHeight = newHeight;

	// Update the viewport to still be all of the window
	glViewport(0, 0, windowWidth, windowHeight);

	// Change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// Load the identity matrix into the projection matrix
	glLoadIdentity();

	// gluPerspective(fovy, aspect, near, far)
	gluPerspective(45, (float)windowWidth / (float)windowHeight, 1, 10000);

	// Change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************

Function:		printControls

Description:	Print the keyboard controls.

*************************************************************************/
void printControls()
{
	printf("Sceen Controls\n");
	printf("----------------\n");
	printf("r:	toggle rings\n");
	printf("s:	toggle stars\n");
	printf("c:	toggle sun's corona\n");
	printf("k:	toggle enterprise shield\n\n");
	printf("Camera Controls\n");
	printf("----------------\n");
	printf("Up Arrow:	move up\n");
	printf("Down Arrow:	move down\n");
	printf("Left Arrow:	move left\n");
	printf("PAGE UP:	forward\n");
	printf("PAGE DOWN:	backward\n\n");
	printf("BONUS\n");
	printf("----------------\n");
	printf("f1:		shoot lasers\n");
	printf("esc/q:	quit application\n");

}
/************************************************************************

Function:		initalizeLasers

Description:	Sets up the lasers to be fired, initally setting them to
				off

*************************************************************************/
void initalizeLasers() {

	// Initally set the lasers to off
	int i;
	for (i = 0; i < MAX_LASERS; i++) {
		lasers[i].shot = 0;
		lasers[i].distance = 0.0;
	}
}



/************************************************************************

Function:		main

Description:	Sets up the openGL rendering context and the windowing
system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	//Parses the enterprise
	parseEnterprise();
	// Randomly generates star positions
	generateStars();
	// Initalize the lasers
	initalizeLasers();
	// Print Keyboard Controls
	printControls();
	// Initialize the toolkit
	glutInit(&argc, argv);
	// Set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// Set window size
	glutInitWindowSize(windowWidth, windowHeight);
	// Set window position on screen
	glutInitWindowPosition(100, 150);
	// Open the screen window
	glutCreateWindow("Assignment 2 - Kyle Asaff");

	// register redraw function
	glutDisplayFunc(myDisplay);
	// register the idle function
	glutIdleFunc(myIdle);
	// register the resize function
	glutReshapeFunc(myResize);

	// Initalize Blending for transparency of sparks
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Process standard key clicks
	glutKeyboardFunc(normalKey);
	// Process special key pressed
	glutSpecialFunc(pressKey);
	// Process special key release
	glutSpecialUpFunc(releaseKey);

	// Initialize the rendering context
	initializeGL();
	// Go into a perpetual loop
	glutMainLoop();
}

