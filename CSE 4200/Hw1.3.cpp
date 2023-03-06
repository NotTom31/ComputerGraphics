#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include "canvas.h"

using namespace std;

Canvas cvs(640, 480, "try out Canvas"); //global canvas object


void drawTree(int n, float x, float y, float size, float angle) {
	if (n == 0) { //end if we finish all the branches
		return;
	}

	if (n > 2) {
		cvs.setColor(1.0, 0.8, 0.7); //set tree brown
	}
	else
		cvs.setColor(0.0, 1.0, 0.2); //set leaves green

	// Draw the current branch
	float x2 = x + size * cos(angle * M_PI / 180.0);
	float y2 = y + size * sin(angle * M_PI / 180.0);
	cvs.moveTo(x, y);
	cvs.lineTo(x2, y2);

	// Draw two smaller branches
	float size_factor = 0.9; // controls the size of the smaller branches
	float angle_factor = 25.0; // controls the angle between the branches
	drawTree(n - 1, x2, y2, size * size_factor, angle + angle_factor);
	drawTree(n - 1, x2, y2, size * size_factor, angle - angle_factor);
}



void display()
{
	cvs.clearScreen();    //clear screen

	drawTree(10, 0, -20, 10, 90);
	glFlush();
}

int main(void)
{
	extern Canvas cvs;
	cvs.setWindow(-60.0, 60.0, -60.0, 60.0);
	cvs.setViewport(0, 500, 0, 500);
	cvs.setBackgroundColor(1.0, 1.0, 1.0);
	cvs.setColor(0.0, 0.0, 0.0);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutDisplayFunc(display);
	glutMainLoop();
}