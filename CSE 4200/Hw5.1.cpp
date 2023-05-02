#include <GL/glut.h>
#include <stdlib.h>

int anglex = 0, angley = 0, anglez = 0;          //rotation angles

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();             /* clear the matrix */
            /* viewing transformation  */
    gluLookAt(3.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
    //   glutWireCube (1.0);

    static GLint vertices[] = { -1, -1, -1,     //0
                                 1, -1, -1,
                                 1, 1, -1,
                                -1, 1, -1,      //3
                                -1, -1, 1,
                                 1, -1, 1,
                                 1, 1, 1,       //6
                                -1, 1, 1        //7
    };

    static GLfloat colors[] = { 0.0, 0.0, 0.0,
                                1.0, 0.0, 0.0,
                                1.0, 1.0, 0.0,
                                0.0, 1.0, 0.0,
                                0.0, 0.0, 1.0,
                                1.0, 0.0, 1.0,
                                1.0, 1.0, 1.0,
                                0.0, 1.0, 1.0,
    };


    glVertexPointer(3, GL_INT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    static GLubyte frontIndices[] = { 4, 5, 6, 7 };
    static GLubyte rightIndices[] = { 1, 2, 6, 5 };
    static GLubyte bottomIndices[] = { 0, 1, 5, 4 };
    static GLubyte backIndices[] = { 0, 3, 2, 1 };
    static GLubyte leftIndices[] = { 0, 4, 7, 3 };
    static GLubyte topIndices[] = { 2, 3, 7, 6 };

    glTranslatef(-1.5, -1.2, 0);

    glRotatef(anglex, 1.0, 0.0, 0.0);           //rotate the object about x-axis
    glRotatef(angley, 0.0, 1.0, 0.0);           //rotate about y-axis   
    glRotatef(anglez, 0.0, 0.0, 1.0);           //rotate about z-axis

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'x':
        anglex = (anglex + 3) % 360;
        break;
    case 'X':
        anglex = (anglex - 3) % 360;
        break;
    case 'y':
        angley = (angley + 3) % 360;
        break;
    case 'Y':
        angley = (angley - 3) % 360;
        break;
    case 'z':
        anglez = (anglez + 3) % 360;
        break;
    case 'Z':
        anglez = (anglez - 3) % 360;
        break;
    case 'r':                                   //reset
        anglez = angley = anglex = 0;
        //lx = ly = lz = 0;
        glLoadIdentity();
        break;
    //case 'a':
    //    lx += 0.3;
    //    break;
    //case 'A':
    //    lx -= 0.3;
    //    break;
    //case 'b':
    //    ly += 0.3;
    //    break;
    //case 'B':
    //    ly -= 0.3;
    //    break;
    //case 'c':
    //    lz += 0.3;
    //    break;
    //case 'C':
    //    lz -= 0.3;
    //    break;
    case 27: /* escape */
        //glutDestroyWindow(window);
        exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
