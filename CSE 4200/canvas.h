//canvas.h
#ifndef CANVAS_H
#define CANVANS_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

// Support Classes for Canvas
class Point2   //single point w/ floating point coordinates
{
public:
  Point2();     //contructor 1
  Point2(float xx, float yy);   //constructor 2
  void set(float xx, float yy);
  float getX();
  float getY();
  void draw(void);
private:
  float x, y;
};

//constructor 1
Point2::Point2()
{
  x = y = 0.0f;
}

//constructor 2
Point2::Point2(float xx, float yy) 
{
  x=xx; y=yy;
} 

void Point2::set(float xx, float yy) 
{
  x=xx; y=yy;
}

float Point2::getX() 
{
  return x;
}

float Point2::getY() 
{
  return y;
}

void Point2::draw(void)
{
  glBegin(GL_POINTS); //draw this point
    glVertex2f((GLfloat)x, (GLfloat)y);
  glEnd();
}

//world window rectangle class
class RealRect   
{
public:
  RealRect(); //constructors
  RealRect(float left, float right, float bottom, float top);
  void set(float left, float right, float bottom, float top);
  float getL(void);     //left boundary
  float getR(void);     //right
  float getT(void);
  float getB(void);
  void draw(void); 	//draw this rectangle using OpenGL
private:
  float l, r, b, t;
};

//constructors
RealRect::RealRect() 
{
  l = 0; r=100; b=0; t=100;
}
 
RealRect::RealRect(float left, float right, float bottom, float top)
{
  l = left; r=right; b=bottom; t=top;
}

void RealRect::set(float left, float right, float bottom, float top)
{
  l=left; r=right; b=bottom; t=top;
}

float RealRect::getL(void)      //left boundary
{
  return l;
}

float RealRect::getR(void)      //right
{
  return r;
}

float RealRect::getT(void)
{
  return t;
}

float RealRect::getB(void)
{
  return b;
}

void RealRect::draw(void)
{
  glRectf( l, b, r, t);
}


class Canvas{
    public:
        Canvas(int width, int height, char* windowTitle){
            char* argv[1]; // dummy argument list for glutInit()
            char dummyString[8];
            argv[0] = dummyString; // hook up the pointer
            int argc = 1; // to satisfy glutInit()
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowSize(width, height);
            glutInitWindowPosition(20, 20);
            glutCreateWindow(windowTitle); // open the screen window
            setWindow(0, (float)width, 0, (float)height); //default world window
            setViewport(0, width, 0, height); // default viewport
            CP.set(0.0f, 0.0f); // initialize the CP to (0, 0)
        }
        void setWindow(float l, float r, float b, float t){
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
            window.set(l, r, b, t);
        }
        void setViewport(int left, int right, int bottom, int top){
            glViewport(left, bottom, right - left, top - bottom);
        }
        //IntRect getViewport(void); // divulge the viewport data
        //RealRect getWindow(void); // divulge the window data
        //float getWindowAspectRatio(void);
        void clearScreen(){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        void setBackgroundColor(float r, float g, float b){
            glClearColor(r, g, b, 1.0);
        }
        void setColor(float r, float g, float b){
            glColor3f(r,g,b);
        }

        void lineTo(GLfloat x, GLfloat y){
        glBegin(GL_LINES); // draw the line
        glVertex2i(CP.getX(), CP.getY());
        glVertex2i(x, y);
        glEnd();
        glFlush();
        CP.set(x, y); // update the CP
        }
        /*
        void lineTo(Point2 p){
            glBegin (GL_LINES);
            glVertex2f((GLfloat) CP.getX(), (GLfloat) CP.getY());
            glVertex2f((GLfloat) p.getX(), (GLfloat) p.getY());
            glEnd();
            CP.set(p.getX(), p.getY());
            glFlush();
        }*/
      /*
        //void lineTo(Point2 p);
        void moveTo(Point2 p) {
            float x1, y1;
            x1 = p.getX();
            y1 = p.getY();
            CP.set(x1, y1);
        }*/
        void moveTo(GLfloat x, GLfloat y)
        {
          CP.set(x,y); // update the CP
        }

        //void moveTo(Point2 p);
        void turnTo(float angle){
            CD = angle;
        }
        void turn(float angle){
            CD += angle;
        }
        void forward(float dist, int isVisible){
            const float RadPerDeg = 0.017453393;          //radians per degree
            float x = CP.getX() + dist * cos ( RadPerDeg * CD );
            float y = CP.getY() + dist * sin ( RadPerDeg * CD );
            if ( isVisible )
                lineTo( x, y );
            else
                moveTo ( x, y );
        }//forward
    private:
        float CD;
        Point2 CP;         //current position in the world
        //IntRect viewport;  //the current viewport 
        RealRect window;   //the current window
};

#endif