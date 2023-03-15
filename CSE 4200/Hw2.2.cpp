#include <GL/glut.h>
#include <stdlib.h>

int i = 0;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void cullFront() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void cullBack() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void click(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && i == 0) {
        i++;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && i >= 1) {
        i = 0;
    }
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_BACK, GL_FILL);
    glColor3f(0.0, 1.0, 0.0);      //green
    if (i == 0) {
        cullBack();
    }
    
    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();

    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1.0, 0.0, 0.0);      //red
    if (i >= 1) {
        cullFront();
    }
    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2f(-50, -50);
    glVertex2f(50, -50);
    glVertex2f(50, 50);
    glVertex2f(-50, 50);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Hw2.2");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);

    glutMouseFunc(click);
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;
}