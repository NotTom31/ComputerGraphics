#include <GL/glut.h>
#include <stdlib.h>


int angleX = 0; 
int angleY = 0;
int angleZ = 0;          //rotation angles

void init(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat red[] = { 0.5f, 0.0f, 0.0f, 1.0f };



    GLfloat light0_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);


    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // set modelview matrix
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // red color

    glLoadIdentity();


    glRotatef(angleX, 1.0, 0.0, 0.0);          
    glRotatef(angleY, 0.0, 1.0, 0.0);          
    glRotatef(angleZ, 0.0, 0.0, 1.0);         

    //Cube 1
    glPushMatrix();
    glTranslatef(-0.5, 0, 0);
    glRotatef(60, 1, 0, 0);
    glRotatef(60, 0, 1, 0);

    glPushAttrib(GL_LIGHTING_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red); 
    glutSolidCube(.4);
    glPopAttrib();
    glPopMatrix();

    //Cube 2
    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    glRotatef(30, 0, 1, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glutSolidCube(.4);
    glPopAttrib();
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'x':
        angleX = (angleX + 3) % 360;
        break;
    case 'X':
        angleX = (angleX - 3) % 360;
        break;
    case 'y':
        angleY = (angleY + 3) % 360;
        break;
    case 'Y':
        angleY = (angleY - 3) % 360;
        break;
    case 'z':
        angleZ = (angleZ + 3) % 360;
        break;
    case 'Z':
        angleZ = (angleZ - 3) % 360;
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
            1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
            1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}