/*
 * tween.cpp
 * Demo of in-between principle and animation. Press 'ESC' to quit the program.
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <sys/time.h>
#include <cmath>

using namespace std;

class Point2 {
public:
    float x;
    float y;
    Point2()
    {
        x = y = 0;
    }
    Point2(float x0, float y0)
    {
        x = x0;	y = y0;
    }
    Point2(const Point2& p)
    {
        x = p.x;
        y = p.y;
    }
};

Point2 tween(const Point2& Q, const Point2& R, float t)
{
    Point2 P;
    P.x = Q.x + (R.x - Q.x) * t;
    P.y = Q.y + (R.y - Q.y) * t;
    return P;
}

void drawTween(const Point2 A[], const Point2 B[], int n, float t, const Point2& c)
{
    glColor3f(0, 0, 0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(8);

    // draw the tween at time t between polylines A and B
    Point2 P0 = tween(A[0], B[0], t);
    Point2 P1 = Point2(P0.x + c.x, P0.y + c.y);
    glBegin(GL_POLYGON);
    for (int i = 1; i < n; i++)
    {
        Point2 P, P2;
        if (i == n)
            P = tween(A[0], B[0], t);
        else
            P = tween(A[i], B[i], t);
        P2 = Point2(P.x + c.x, P.y + c.y);
        glVertex2f(P2.x, P2.y);
        P1 = P2;
    }
    glEnd();
}


void makeSquare(Point2 S[]) {
    // Define vertices of square
    S[0].x = -1.0; S[0].y = 1.0;
    S[1].x = 1.0; S[1].y = 1.0;
    S[2].x = 1.0; S[2].y = -1.0;
    S[3].x = -1.0; S[3].y = -1.0;
    S[4].x = -1.0; S[4].y = 1.0;
    S[5].x = -1.0; S[0].y = 1.0;
    S[6].x = 1.0; S[1].y = 1.0;
    S[7].x = 1.0; S[2].y = -1.0;
    S[8].x = -1.0; S[3].y = -1.0;
    S[9].x = -1.0; S[4].y = 1.0;
    S[10].x = -1.0; S[0].y = 1.0;
    S[11].x = 1.0; S[1].y = 1.0;
    S[12].x = 1.0; S[2].y = -1.0;
    S[13].x = -1.0; S[3].y = -1.0;
    S[14].x = -1.0; S[4].y = 1.0;
    S[15].x = -1.0; S[0].y = 1.0;
    S[16].x = 1.0; S[1].y = 1.0;
    S[17].x = 1.0; S[2].y = -1.0;
    S[18].x = -1.0; S[3].y = -1.0;
    S[19].x = -1.0; S[4].y = 1.0;
    S[20].x = -1.0; S[0].y = 1.0;
    S[21].x = 1.0; S[1].y = 1.0;
    S[22].x = 1.0; S[2].y = -1.0;
    S[23].x = -1.0; S[3].y = -1.0;
    S[24].x = -1.0; S[4].y = 1.0;
    S[25].x = -1.0; S[0].y = 1.0;
    S[26].x = 1.0; S[1].y = 1.0;
    S[27].x = 1.0; S[2].y = -1.0;
    S[28].x = -1.0; S[3].y = -1.0;
    S[29].x = -1.0; S[4].y = 1.0;
}

void makeCircle(Point2 C[]) {
    int n = 29; //number of sides the polygon will have
    float angle = 5 * 3.14159 / n; //angle between two vertices
    float radius = 3; //1 is the default
    for (int i = 0; i < n; i++) {
        float x = radius * cos(i * angle);
        float y = radius * sin(i * angle);
        C[i].x = x; C[i].y = y;
    }
}

Point2 square[30];
Point2 circle[30];
Point2 center(5, 15);
float t = 0, deltat = 0.1;
float deltax = 2, deltay = 0;
void init(void)
{
    gluOrtho2D(0.0, 30.0, 0.0, 30.0);
    makeSquare(square);
    makeCircle(circle);

    glLineWidth(2);
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawTween(square, circle, 30, t, center);

    glFlush();
    glutSwapBuffers();
}

void animate()
{
    t += deltat;
    center.x += deltax;	center.y += deltay;  	//move center for clarity of display
    if (t > 1) {
        t = 1.0;
        deltat = -deltat;			//reverse direction
        deltax = -deltax;
        deltay = -deltay;
    }
    else if (t < 0) {
        t = 0;
        deltat = -deltat;			//reverse direction
        deltax = -deltax;
        deltay = -deltay;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'a':
        animate();
        break;
    case 'r':
        deltat = -deltat;       //reverse direction
        deltax = -deltax;
        deltay = -deltay;
        animate();
        break;
    }
}

void timerHandle(int value)
{
    animate();
    glutPostRedisplay();
    // call timerHandle 100 ms later, value 0 is passed to timerHandle (not used here)
    glutTimerFunc(100, timerHandle, 0);
}

void visHandle(int visible)
{
    if (visible == GLUT_VISIBLE)
        timerHandle(0);
    else
        ;
}

int main(int argc, char* argv[])
{
    // Set things (glut) up 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Create the window and handlers 
    glutCreateWindow("Tweening Demo");
    glutReshapeWindow(500, 500);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutVisibilityFunc(visHandle);
    init();
    //perpetual loop
    glutMainLoop();
    return(0);
}

static unsigned int get_ticks()
{
    struct timeval t;

    gettimeofday(&t, NULL);

    return (t.tv_sec * 1000) + (t.tv_usec / 1000);
}

