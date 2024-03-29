#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include "canvas.h"

int H = 480;
int W = 640;

Canvas cvs(W, H, (char*)"Try out Canvas");

void drawSpiral(double a, double b, double scale, double length, double increment) {
    //glBegin(GL_LINE_STRIP);
    double x, y;
    cvs.moveTo(x, y);
    for (double t = 0; t <= length * M_PI; t += increment) {
        x = (a + b * t) * scale * cos(t);
        y = (a + b * t) * scale * sin(t);
        cvs.lineTo(x, y);
    }
    //glEnd();
}

void display() {
    cvs.clearScreen();    //clear screen
    cvs.setColor(1.0, 0.2, 0.5);
    cvs.moveTo(0.0, 0.0);
    cvs.turnTo(0.0);
    // Draw Archimedean spirals in four quadrants
    glPushMatrix();
    //cvs.setViewport(200, 0, 200, 0);
    glTranslated(200, 200, 0);
    drawSpiral(0.2, 1, 3, 15, 0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-200, 200, 0);
    drawSpiral(0.05, 1, 2, 13, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-200, -200, 0);
    drawSpiral(0.1, 1, 5, 16, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(200, -200, 0);
    drawSpiral(0.1, .9, 4, 11, 0.4);
    glPopMatrix();

    glFlush();
}


int main(void)
{
    extern Canvas cvs;
    cvs.setWindow(-500.0, 500.0, -500.0, 500.0);
    cvs.setViewport(0, 500, 0, 500);
    cvs.setBackgroundColor(1.0, 1.0, 1.0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutDisplayFunc(display);
    glutMainLoop();
}