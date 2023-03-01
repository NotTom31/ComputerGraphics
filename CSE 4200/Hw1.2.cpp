#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

using namespace std;

const int VWIDTH = 640;
const int VHEIGHT = 480;

double currentX;
double currentY;

double f(double x) {
    double y = exp(-fabs(x)) * sin(2 * 3.1415926 * x);
    //double y = sin(x) / x;
    //double y = exp(x) / pow(x, 2);
    return y;
}

void moveTo(double x, double y) {
    currentX = x;
    currentY = y;
}

void lineTo(double x, double y) {
    
    glVertex2f(currentX, currentY);
    glVertex2f(x, y);
    glEnd();
    currentX = x;
    currentY = y;
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(1.0);
    gluOrtho2D(-5, 4, -1, 1);
    glLineWidth(2);
}

void drawPoint() {

    double x; double y;
    moveTo(-10, 0);
    for (x = -10; x < 10; x += .005) {
        y = f(x);
        glBegin(GL_POINTS);
        lineTo(x, y);
    }
}

//void drawCurve() {
//
//    double x; double y;
//    moveTo(-10, 0);
//    for (x = -10; x < 10; x += .005) {
//        y = f(x);
//        glBegin(GL_LINES);
//        lineTo(x, y);
//    }
//}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    //glViewport(VWIDTH / 8, VHEIGHT / 2, VWIDTH / 2, VHEIGHT / 2);
    //drawCurve();
    drawPoint();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(VWIDTH, VHEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Plots");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}