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
    //double y = exp(-fabs(x)) * cos(2 * 3.1415926 * x);
    //double y = sin(x) / x;
    double y = exp(x) / pow(x, 2);
    return y;
}

double g(double x) {
    //double y = exp(-fabs(x)) * cos(2 * 3.1415926 * x);
    double y = sin(x) / x;
    //double y = pow(exp(x), x) / pow(x, 2);
    return y;
}

void moveTo(double x, double y) {
    currentX = x;
    currentY = y;
}

void lineTo(double x, double y) {
    glBegin(GL_LINES);
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
    gluOrtho2D(0.0, 7.0, -5, 5);
    glLineWidth(2);
}

void drawCurve() {
    double x, y;
    moveTo(0, 0);
    
    //glEnable(GL_LINE_STIPPLE);
    //glLineStipple(1, 0x00FF);
    for (x = 0; x < 2*3.1415926; x += 1) {
        y = g(x);
        lineTo(x, y);
    }
    //glDisable(GL_LINE_STIPPLE);
}

void drawCurve2() {
    double x, y;
    moveTo(0, 0);
    
    //glEnable(GL_LINE_STIPPLE);
    //glLineStipple(1, 0x00FF);
    for (x = 0; x < 20; x += 0.1) {
        y = f(x);
        lineTo(x, y);
    }
    //glDisable(GL_LINE_STIPPLE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glColor3f(1, 0, 0);

    glLineStipple(2, 0x0F0F);
    glViewport(VWIDTH/8, VHEIGHT/2, VWIDTH / 2, VHEIGHT / 2);
    drawCurve();
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00AA);
    glViewport(3*VWIDTH / 4, 0, VWIDTH / 4, VHEIGHT / 4);
    drawCurve2();
    glDisable(GL_LINE_STIPPLE);
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