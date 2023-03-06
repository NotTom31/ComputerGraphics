#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

int startX, startY, endX, endY;
int xone, yone, xtwo, ytwo, xthree, ythree;
bool Rect = true;
int clickCount = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set rectangle color to green

    // Draw the rectangle using the start and end points
    if (Rect && clickCount == 1) {
        glBegin(GL_QUADS);
        glVertex2i(startX, startY);
        glVertex2i(endX, startY);
        glVertex2i(endX, endY);
        glVertex2i(startX, endY);
        glEnd();
    }
    else if (!Rect && clickCount == 2) {
        glBegin(GL_TRIANGLES);
        glVertex2i(xone, yone);
        glVertex2i(xtwo, ytwo);
        glVertex2i(xthree, ythree);
        glEnd();
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
        Rect = true;
        //startX = 0; startY = 0; endX = 0; endY = 0; xone = 0; yone = 0; xtwo = 0; ytwo = 0; xthree = 0; ythree = 0;
        //clickCount = 0;
		break;
	case 't':
        Rect = false;
        //startX = 0; startY = 0; endX = 0; endY = 0; xone = 0; yone = 0; xtwo = 0; ytwo = 0; xthree = 0; ythree = 0;
        //clickCount = 0;
		break;
	case 'q':
		exit(0);
		break;


	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (Rect) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickCount == 0)
        {
            startX = x; // Set the start X-coordinate of the rectangle
            startY = glutGet(GLUT_WINDOW_HEIGHT) - y; // Set the start Y-coordinate of the rectangle (invert y-coordinate)
            clickCount += 1;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickCount == 1)
        {
            endX = x; // Set the end X-coordinate of the rectangle
            endY = glutGet(GLUT_WINDOW_HEIGHT) - y; // Set the end Y-coordinate of the rectangle (invert y-coordinate)

            glutPostRedisplay(); // Trigger a redraw of the window
            clickCount = 0; //reset click count
        }
    }
    else { //triangle
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickCount == 0)
        {
            xone = x; // Set the start X-coordinate of the triangle
            yone = glutGet(GLUT_WINDOW_HEIGHT) - y; // Set the start Y-coordinate of the triangle (invert y-coordinate)
            clickCount += 1;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickCount == 1)
        {
            xtwo = x; // Set the start X-coordinate of the triangle
            ytwo = glutGet(GLUT_WINDOW_HEIGHT) - y; // Set the start Y-coordinate of the triangle (invert y-coordinate)
            clickCount += 1;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickCount == 2)
        {
            xthree = x; // Set the end X-coordinate of the triangle
            ythree = glutGet(GLUT_WINDOW_HEIGHT) - y; // Set the end Y-coordinate of the triangle (invert y-coordinate)

            glutPostRedisplay(); // Trigger a redraw of the window
            clickCount = 0; //reset click count
        }
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rectangle");

    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    gluOrtho2D(0, 500, 0, 500); // Set the viewing window

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
