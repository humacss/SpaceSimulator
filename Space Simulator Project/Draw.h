/****************************************************************************
*   FILE: Draw.h
*
*   FUNCTION: This class is responsible for ALL drawing done in the application.
*   It uses a window as the target for drawing and a space for the content to
*   draw. The class manages GLUT fucntion calls, variables, user-input,
*   scaling from window coordinates to real coordinates and vice versa.
*
*   PURPOSE: By collecting all the drawing done in the application in one
*   class it keeps the cohesion at a manageable level. It might also make it
*   easier to draw in multiple windows later on if it will ever be supported.
*
****************************************************************************/

#ifndef _Draw_
#define _Draw_

#include "Window.h"
#include "Space.h"
#include <GL/glut.h>
#include <windows.h>

/* Solution for encapsulating GLUT inspired by:
    http://paulsolt.com/2009/07/openglglut-classes-oop-and-problems/ */

class Draw{
    public:
    /** Constructors    **/
    //  constructs a draw object with a target window to draw in,
    //  a space to draw and a double starting scale
    Draw(Window*, Space*, double);

    /** Member Functions   **/
    //  starts the GLUT main loop
    void            Start();
    //  draws a sphere at a coordinate with a double size
    void            DrawSphere(Coordinate, double);
    //  scale a meters double to screen percentage
    double          ToScale(double);
    //  scale a screen percentage double to meters
    double          FromScale(double);
    // draw all the stars in space
    void            DrawStars();
    //  draw all the planets in space
    void            DrawPlanets();
    //  draw all the moons in space
    void            DrawMoons();
    //  draws lighting on the argument star
    void            DrawLighting(Star*);
    //  draws lighting on the argument planet
    void            DrawLighting(Planet*);
    //  draws lighting on the argument moon
    void            DrawLighting(Moon*);

    /** Functions called by GLUT  **/
    //  calls my own non-static display handler
    static void     DisplayWrapper()
                        {mspInstance->Display();}
    //  calls my own non-static idle handler
    static void     IdleWrapper()
                        {mspInstance->Idle();};
    //  calls my own non-static keyboard-input handler
    static void     KeyboardWrapper(unsigned char key, int x, int y)
                        {mspInstance->Keyboard(key, x, y);}
    //  calls my own non-static mouse-input handler
    static void     MouseWrapper(int button, int state, int x, int y)
                        {mspInstance->Mouse(button, state, x, y);}

    /** My own non-static GLUT functions **/
    //  displays everything in the space
    void            Display();
    //  the function called when GLUT is idle
    void            Idle();
    //  the function called when an ASCII key is pressed
    void            Keyboard(unsigned char, int, int);
    //  the function called when a mouse button is clicked
    void            Mouse(int, int, int, int);

    /** Getters and Setters **/
    static void     SetInstance(Draw * instance);
    void            SetScale(double scaleAu){mScaleAu = scaleAu;}
    double          GetScale(){return mScaleAu;}
    double          CalculateNewObjectSpeed(int, int);

    private:
    /** Class members   **/
    static  Draw*                       mspInstance;
    Window*                             mpWindow;
    Space*                              mpSpace;
    double                              mScaleAu;
    std::list<SpaceObject*>             mLookAt;
    std::list<SpaceObject*>::iterator   mLookAtIterator;

};

#endif
