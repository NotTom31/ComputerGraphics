#include <GL/glut.h>
#include <cmath>

const int num_sides = 8; // number of sides in the octagon
const float radius = 0.5; // radius of the octagon
const float height = 0.2; // height of the sandwich

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set up lighting and material properties
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    // set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // draw top octagon
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_sides; ++i) {
        float theta = 2.0 * M_PI * i / num_sides;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(x, y, height / 2.0);
    }
    glEnd();

    // draw bottom octagon
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_sides; ++i) {
        float theta = 2.0 * M_PI * i / num_sides;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(x, y, -height / 2.0);
    }
    glEnd();

    // draw sides
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < num_sides; ++i) {
        float theta = 2.0 * M_PI * i / num_sides;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        // calculate vertices for the sandwich
        float x1 = (radius - 0.05) * cos(theta);
        float y1 = (radius - 0.05) * sin(theta);
        float z1 = -height / 2.0;

        float x2 = (radius - 0.05) * cos(theta);
        float y2 = (radius - 0.05) * sin(theta);
        float z2 = height / 2.0;

        // calculate normal vector for lighting
        float nx = cos(theta);
        float ny = sin(theta);
        float nz = 0.0;

        glNormal3f(nx, ny, nz);

        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Octagon Sandwich");
    glutDisplayFunc(display);

    glClearColor(0.5, 0.5, 0.5, 1.0);

    glEnable(GL_NORMALIZE);

    glutMainLoop();

    return 0;
}
