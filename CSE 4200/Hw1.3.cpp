//draw_main.cpp: main loop of drawing program

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//initialization
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
    glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
    glPointSize(4.0);			//a dot is 4x4
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();			//replace current matrix with identity matrix
    gluOrtho2D(-12.0, 12.0, 20.0, -15.0);
}

void makecylinder(float height, float Base)
{
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glColor3f(0, 0, 0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(qobj, Base, Base - (0.2 * Base), height, 20, 20);
	glPopMatrix();
}

void maketree(float height, float Base)
{

	glPushMatrix();
	float angle;
	makecylinder(height, Base);
	glTranslatef(0.0, height, 0.0);
	height -= height * 0.2;
	Base -= Base * 0.3;

	if (height > 1)
	{
		angle = 30;
		glPushMatrix();
		glRotatef(angle, -1.0, 0.0, 0.0);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5, 0.0, 0.866);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5, 0.0, -0.866);
		maketree(height, Base);
		glPopMatrix();
	}
	glPopMatrix();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);	//clear screen
    glBegin(GL_LINES);			//draw points
	maketree(4.0, 0.1);

    glEnd();
    glFlush();				//send all output to screen
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGB display mode, depth buffer.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);	//initialize toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//set display mode: single bufferring, RGBA model
    glutInitWindowSize(500, 500);		//set window size on screen
    glutInitWindowPosition(100, 150); 	//set window position on screen
    glutCreateWindow(argv[0]);		//open screen window
    init();
    glutDisplayFunc(display);		//points to display function
    glutMainLoop();			//go into perpetual loop
    return 0;
}