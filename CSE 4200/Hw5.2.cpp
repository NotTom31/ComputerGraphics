#include <GL/glut.h>

void init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat light0_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

    GLfloat light1_pos[] = { -1.0f, -1.0f, -1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);

    GLfloat light2_pos[] = { 0.0f, -1.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW); // set modelview matrix
    GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // blue color
    GLfloat green[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // green color
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // red color

    // render sphere B
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glPushAttrib(GL_LIGHTING_BIT); //save material and lighting
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green); // set material color
    glutSolidSphere(0.25, 20, 20); // render sphere
    glPopAttrib();
    glPopMatrix();

    // render sphere C
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glPushAttrib(GL_LIGHTING_BIT); //save material and lighting
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue); // set material color
    glutSolidSphere(0.25, 20, 20); // render sphere
    glPopAttrib();
    glPopMatrix();

    // render sphere A
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glPushAttrib(GL_LIGHTING_BIT); //save material and lighting
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red); // set material color
    glutSolidSphere(0.25, 20, 20); // render sphere
    glPopAttrib();
    glPopMatrix();

    glutSwapBuffers(); // swap buffers
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize glut
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // set display mode
    glutInitWindowSize(640, 480); // set window size
    glutCreateWindow("Three Lit Spheres"); // create window
    init(); // initialize scene
    glutDisplayFunc(display); // set display function
    glutMainLoop(); // enter the main loop
    return 0; // exit program
}