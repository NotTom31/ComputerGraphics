//canvas.h
#ifndef CANVAS_H
#define CANVANS_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

class Canvas{
    public:
        Canvas(int width, int height, char* windowTitle){
            char* argv[1];  //dummy argument list for glutinit()
            char dummyString[8];
            argv[0] = dummyString;  //hook up the pointer
            int argc = 1;

            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowSize(width, height);
            glutInitWindowPosition (20,20);
            glutCreateWindow (windowTitle);
            setWindow(0, (float)width, 0, (float)height); // default world window
            setViewport (0, width, 0, height); //default viewport
            CP.set(0.0f, 0.0f); //initialize the cp to (0,0)
        } // constructor
        void setWindow(float l, float r, float b, float t){
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
            window.set(l, r, b, t);
        }
        void setViewport(int l, int r, int b, int t);
        //IntRect getViewport(void); // divulge the viewport data
        RealRect getWindow(void); // divulge the window data
        float getWindowAspectRatio(void);
        void clearScreen();
        void setBackgroundColor(float r, float g, float b);
        void setColor(float r, float g, float b);
        void lineTo(float x, float y)
        {
            glBegin(GL_LINES);
                glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
                glVertex2f((GLfloat)x, (GLfloat)y); // draw the line
            glEnd();
            CP.set(x, y); // update the CP
            glFlush();
        }
        void lineTo(Point2 p){
            glBegin (GL_LINES);
                glVertex2f((GLfloat) CP.getX(), (GLfloat) CP.getY());
                glVertex2f((GLfloat) p.getX(), (GLfloat) p.getY());
            glEnd();
            CP.set(p.getX(), p.getY());
            glFlush();
        }
        void moveTo(float x, float y){
            CP.set(x, y);
        }
        void moveTo(Point2 p){
            float x1, y1;
            x1 = p.getX();
            y1 = p.getY();
            CP.set(x1, y1);
        }
        void moveRel(float dx, float dy){
            CP.set(CP.getX() + dx, CP.getY() + dy);
        }
        void lineRel(float dx, float dy)
        {
            float x = CP.getX() + dx, y = CP.getY() + dy;
            lineTo(x, y);
            CP.set(x, y);
        }
        void turnTo(float angle){
            CD = angle;
        }
        void turn(float angle){
            CD += angle;
        }
        void forward(float dist, int isVisible){
            const float RadPerDeg = 0.017453393; //radians per degree
            float x = CP.getX() + dist * cos(RadPerDeg * CD);
            float y = CP.getY() + dist * sin(RadPerDeg * CD);
            if(isVisible)
                lineTo(x, y);
            else
                moveTo(x, y);
        }
    private:
        float CD;
        Point2 CP;         //current position in the world
        //IntRect viewport;  //the current viewport 
        RealRect window;   //the current window
};

// Support Classes for Canvas
class Point2   //single point w/ floating point coordinates
{
public:
    Point2(){
        x = y = 0.0f;
    }    //contructor 1
    Point2(float xx, float yy){
        x=xx; y=yy;
    }    //constructor 2
    void set(float xx, float yy){
        x=xx; y=yy;
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }
    void draw(void){
        glBegin(GL_POINTS); //draw this point
            glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }
private:
    float x, y;
};

//world window rectangle class
class RealRect   
{
public:
    RealRect(){
        l = 0; r=100; b=0; t=100;
    } //constructors
    RealRect(float left, float right, float bottom, float top){
    l = left; r=right; b=bottom; t=top;
    }
    void set(float left, float right, float bottom, float top){
        l=left; r=right; b=bottom; t=top;
    }
    float getL(void){
        return l;
    }     //left boundary
    float getR(void){
        return r;
    }     //right
    float getT(void){
        return t;
    }
    float getB(void){
        return b;
    }
    void draw(void){
        glRectf( l, b, r, t);
    }	//draw this rectangle using OpenGL
    private:
        float l, r, b, t;
};

#endif