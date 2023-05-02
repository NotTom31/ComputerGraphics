/* 
 * triangles1.cpp
 * Simple shadow of triangles for CPATH.
 * Assume that shadows formed on the gound at y = 0.
 * Ground is created using quads with slightly negative y values.
 * @Author: Tong Lai Yu
 * Feb. 2011
 */
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//data for triangles 
//GLfloat vertices[] = {-1.0,-1.0,-1.0,1.0,-1.0,-1.0,
//	1.0,1.0,-1.0, -1.0,1.0,-1.0, -1.0,-1.0,1.0, 
//	1.0,-1.0,1.0, 1.0,1.0,1.0, -1.0,1.0,1.0};
GLfloat vertices[] = {-1.0,2.0,-1.0, 1.0,2.0,-1.0,
	1.0,4.0,-1.0, -1.0,4.0,-1.0, -1.0,2.0,1.0, 
	1.0,2.0,1.0, 1.0,4.0,1.0, -1.0,4.0,1.0};

GLfloat colors[] = {0.0,0.0,0.0,1.0,0.0,0.0,
	1.0,1.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0, 
	1.0,0.0,1.0, 1.0,1.0,1.0, 0.0,1.0,1.0};

GLfloat bcolors[] = {0.0,0.0,0.0,0.0,0.0,0.0,
	0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 
	0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0};

GLubyte triangleIndices[]={0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4};

int anglex= 0, angley = 0, anglez = 0;          //rotation angles
double lx = 0, ly = 0, lz = 0;   //translation for light source
int window;

void drawGround()
{
  //use grid to form the ground and perturb its normals
  glColor3f ( 0.0, 1.0, 0.0 );
  glBegin ( GL_QUADS );
   double x, z = 4.0;
   int colorturn = 0;
   for ( int i = 0; i < 40; i++ ){
     x = -4.0;
     for ( int j = 0; j < 40; j++ ) {
       glVertex3f ( x, -0.01, z );
       glVertex3f ( x+0.2, -0.01, z );
       glVertex3f ( x+0.2, -0.01, z-0.2 );
       glVertex3f ( x, -0.01, z-0.2 );
       x += 0.2;
       if ( colorturn++ % 2 == 0 )
        glColor3f ( 0.0, 1.0, 0.0 );
       else
        glColor3f ( 1.0, 0.0, 0.0 );
     }
     z -= 0.2;
     colorturn++;
   }
  glEnd();
}

void display(void)
{

  //GLfloat light0[3]={0.0, 20.0, 0.0};
  GLfloat light0[3]={0.0, 6.0, 0.0};
  GLfloat light[3];
  GLfloat m[16];			//projection matrix
  
  light[0] = light0[0] + lx;
  light[1] = light0[1] + ly;
  light[2] = light0[2] + lz;

  int i,j;
  for(i=0;i<16;i++) 
    m[i]=0.0;
  //set projection matrix
  m[0] = m[5] = m[10] = 1.0;
  m[7]=-1.0 / light[1];			//light[1] is y-coordinate of light

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace ( GL_BACK );               //do not display any back face
  glLoadIdentity();
  gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

  //show the light position
  glColor3f ( 1, 0, 0 );
  glPointSize ( 8 );
 // glPushMatrix();
 // glTranslatef( lx, ly, lz );
  glBegin ( GL_POINT );
    glVertex3f ( light[0], light[1], light[2] );
  glEnd();

  //Draw the ground
  drawGround();

//  glPopMatrix();
  glPushMatrix();

//  glTranslatef(0.0, 3.0, 0.0);
  glRotatef( anglex, 1.0, 0.0, 0.0);           //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);           //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);           //rotate about z-axis

  //display the cube
  glColorPointer(3,GL_FLOAT, 0, colors); 
 // glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, triangleIndices);
  glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, triangleIndices);

  glPopMatrix();
  // Note that matrix operation is in reverse
  //   order of instructions

  glTranslatef(light[0], light[1],light[2]);    // move everything back
  glMultMatrixf(m);                             // projection matrix is simple for projection from origin
  glTranslatef(-light[0], -light[1],-light[2]); // move light source to origin
  glColor3f(0.2,0.2,0.2);			// dark

  glPushMatrix();
  glRotatef( anglex, 1.0, 0.0, 0.0);           //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);           //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);           //rotate about z-axis
  //The shadow
  glColorPointer(3,GL_FLOAT, 0, bcolors); 
 // glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, triangleIndices);
  glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, triangleIndices);

  glPopMatrix();
  glutSwapBuffers(); 
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -3.0 * (GLfloat) h / (GLfloat) w,
            5.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -3.0, 5.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 'r':                                   //reset
      anglez = angley = anglex = 0;
      lx = ly = lz = 0;
      glLoadIdentity();
      break;
    case 'a':
      lx += 0.3;
      break;
    case 'A':
      lx -= 0.3;
      break;
    case 'b':
      ly += 0.3;
      break;
    case 'B':
      ly -= 0.3;
      break;
    case 'c':
      lz += 0.3;
      break;
    case 'C':
      lz -= 0.3;
      break;
  case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{

/* need both double buffering and z buffer */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    window = glutCreateWindow( argv[0] );
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glEnableClientState(GL_COLOR_ARRAY); 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3,GL_FLOAT, 0, colors); 
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,1.0,1.0);
    glutKeyboardFunc (keyboard);
    glutMainLoop();

    return 0;
}
