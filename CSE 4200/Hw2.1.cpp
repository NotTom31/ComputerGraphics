#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include "canvas.h"

int H = 480;
int W = 640;

Canvas cvs(W, H, (char*)"Hw2.1");

void drawLogSpiral(double scale) {
    //cvs.setWindow(-100, 100, -100, 100);
    double K = 0.1, a = 1, x, y, f, t;
    const double pi = 3.14159;
    t = 0;
    f = K * exp(a * t);
    x = f * cos(t);
    y = f * sin(t);
    glBegin(GL_LINE_STRIP);
    for (t = 0; t <= 16 * pi; t += 0.1) {
        f = K * exp(a * t);
        x = f * cos(t);
        y = f * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawArcSpiral(double a, double scale, double theta, double increment) {
    glBegin(GL_LINE_STRIP);
    double x, y;
    //cvs.moveTo(x, y);
    for (double t = 0; t <= theta * M_PI; t += increment) {
        x = (a * t) * scale * cos(t);
        y = (a * t) * scale * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawRose() {
    double x, y, f;
    //cvs.moveTo(x, y);
    glBegin(GL_LINE_STRIP);
    for (float theta = 0; theta <= 2 * M_PI; theta += 0.01) {
        f = cos(8 * theta);
        x = 200 * f * cos(theta);
        y = 200 * f * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCardioid() {
    double x, y, f, K = 3, t = 2;
    glBegin(GL_LINE_STRIP);
    

    for (float theta = 0; theta <= 2 * M_PI; theta += 0.01) {
        f = K * (1 + cos(theta));
        x = 60 * f * cos(theta);
        y = 60 * f * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    cvs.clearScreen();    //clear screen
    cvs.setColor(1.0, 0.2, 0.5);
    cvs.moveTo(0.0, 0.0);
    cvs.turnTo(0.0);

    glPushMatrix();
    glTranslated(300, 300, 0);
    drawArcSpiral(1, 3, 24, 0.1);
    glPopMatrix();

    glPushMatrix();
    //cvs.setViewport(200, 0, 200, 0);
    glTranslated(-300, 300, 0);
    drawLogSpiral(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-300, -300, 0);
    drawRose();
    glPopMatrix();

    glPushMatrix();
    glTranslated(300, -300, 0);
    drawCardioid();
    glPopMatrix();

    glFlush();
}


int main(void)
{
    extern Canvas cvs;
    cvs.setWindow(-700.0, 700.0, -700.0, 700.0);
    cvs.setViewport(0, 500, 0, 500);
    cvs.setBackgroundColor(1.0, 1.0, 1.0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutDisplayFunc(display);
    glutMainLoop();
}