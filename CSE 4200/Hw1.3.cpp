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
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void drawSpiral() {
    //cvs.setWindow(-100, 100, -100, 100);
    double K = 0.01, a = 0.35, x, y, f, t;
    const double pi = 3.14159;
    t = 0;
    f = K * exp(a * t);
    x = f * cos(t);
    y = f * sin(t);
    cvs.moveTo(x, y);
    for (t = 0; t <= 8 * pi; t += 0.1) {
        f = K * exp(a * t);
        x = f * cos(t);
        y = f * sin(t);
        cvs.lineTo(x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);	//clear screen
    glBegin(GL_POINTS);			//draw points


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