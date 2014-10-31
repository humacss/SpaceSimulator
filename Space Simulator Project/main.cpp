/****************************************************************************
*   TITLE: Space Simulator
*
*   LAST MODIFIED: 15th of May 2011, 18:09 PM, +2 GMT
*
*   AUTHOR: Johan Näslund
*
*   DESCRIPTION: This application is a simulator of the universe and the
*   gravitational laws within it. It manages a space containing different
*   space objects and calculates the gravity between them to simulate a
*   universe.
*
*   The application responds to some user input (see the
*   "Space Simulator Overview.docx" file) and displays simple graphics
*   drawn with OpenGL - GLUT.
*
*   REQUIREMENTS:
*   •   The code was written entirely in the Code::Blocks IDE. To compile the
*   code glut.h, libglut32.a and glut32.dll has to be added to the IDE and
*   system folders if these aren't included already. These files can be found
*   in the 'dependencies' folder, together with some simple instructions.
*   •   The code has only been tested to compile on the Windows Vista
*   Operating System. It will most likely also run on all other Windows
*   Operating systems released after Windows 95. On the earlier versions
*   support for OpenGL has to be installed manually.
*
*   NOTES:
*   •   At the time of the creation of this program I had no experience
*   with GLUT before and very little experience with OpenGL. Therefore the
*   code concerning GLUT and OpenGL will probably not be optimal. It was
*   simply a means to an end of presenting my results in a more concrete way.
*   •   All the lines within the code have been kept at 78 characters long
*   for the sake of proper printing line length.
*   •   The coding standard used in this project is inspired by:
*       http://www.possibility.com/Cpp/CppCodingStandard.html
*
*   TODO:
*   •   Have the radius of the objects in space scale with the map scale.
*   (However at the moment that isn't of a very high priority and as such it
    has been left on the todo list.)
*
****************************************************************************/

/****************************************************************************
*   FILE: main.cpp
*
*   FUNCTION: The file containing the main function.
*
*   PURPOSE: The reason for keeping the main function in a separate file is to
*   keep an easy to understand structure of the code, anyone can easily find
*   and edit the code that is executed at run-time.
*
****************************************************************************/

#include "Draw.h"
#include "Space.h"

/**
    Name: main(int, char*)
    Function: Contains the code to be executed at run-time.
**/
int main(int argc, char* argv[]){
    //  create and initialize window
    Window window("Space Simulator", 800, 800, argc, argv);
    window.Initialize();

    /*  START: Create the universe   */
    //  construct a space
    //  the argument given is how many seconds should pass per update,
    //  less seconds per update yields more accurate simulation
    Space space(150);
    /*  START: Declare objects  */
    Star* sun =         new Star("Sun", //name
                                 1.9891e30, //mass
                                 0.025,   //radius
                                 Coordinate(0, 0), //position
                                 Coordinate(0, 0), //velocity
                                 1.00, 1.00, 0.00); //rgb colour
    Planet* mercury =   new Planet("Mercury", //name
                                   6.083e10, //mass
                                   0.0125, //radius
                                   Coordinate(5790906e4, 0), //position
                                   Coordinate(0, 47870), //velocity
                                   0.6, 0.6, 0.6); //rgb colour
    Planet* venus =     new Planet("Venus", 4.8685e24, 0.0125,
                                   Coordinate(1082089e5, 0),
                                   Coordinate(0, 35020),
                                   1.0, 0.5, 0.5);
    Planet* earth =     new Planet("Earth", 5.9736e24, 0.0125,
                                   Coordinate(149598261e3,  0),
                                   Coordinate(0, 29783),
                                   0, 1.0, 0);
    Planet* mars =      new Planet("Mars", 4.185e23, 0.0125 ,
                                   Coordinate(227939100e3, 0),
                                   Coordinate(0, 24077),
                                   1.0, 0, 0);
    Planet* jupiter =   new Planet("Jupiter",1.8986e27, 0.0125,
                                   Coordinate(778547200e3, 0),
                                   Coordinate(0, 13.07e3),
                                   0.8 ,0.4 ,0);
    Planet* saturn =    new Planet("Saturn",8.2713e14, 0.0125,
                                   Coordinate(1433449370e3, 0),
                                   Coordinate(0, 9.69e3),
                                   0.7, 0.5, 0);
    Planet* uranus =    new Planet("Uranus",8.6810e25, 0.0125,
                                   Coordinate(2876679082e3, 0),
                                   Coordinate(0, 6.81e3),
                                   0, 0, 0.8);
    Planet* neptune =   new Planet("Neptune", 1.0243e26, 0.0125,
                                   Coordinate(4452940833e3, 0),
                                   Coordinate(0, 5.43e3),
                                   0, 0, 1.0);
    Moon* moon =        new Moon(earth, //"owner" planet
                                 "Moon", //name
                                 7.3477e22,  //mass
                                 0.00625,   //radius
                                 384399e3, //distance from owner
                                 0.8, 0.8, 0.8); //rgb colour
    Moon* mJupiter =    new Moon(jupiter, "Moon", 7.3477e22,
                                 0.00625, 184399e4, 0.8, 0.8, 0.8);

    /*  END: Declaration of objects */
    /*  START: Add objects to space */
    space.AddObjectToSpace(sun);
    space.AddObjectToSpace(mercury);
    space.AddObjectToSpace(venus);
    space.AddObjectToSpace(earth);
    space.AddObjectToSpace(moon);
    space.AddObjectToSpace(mars);
    space.AddObjectToSpace(jupiter);
    space.AddObjectToSpace(mJupiter);
    space.AddObjectToSpace(saturn);
    space.AddObjectToSpace(uranus);
    space.AddObjectToSpace(neptune);
    /*  END: Add objects to space   */
    /*  END: Create the universe */
    /*  START: Construct the draw object    */
    //  give the draw class object pointers to
    //  the window to draw in and the space to draw
    Draw * draw = new Draw(&window, &space, 10);
    //  sets the instance to this draw
    draw->SetInstance(draw);
    /*  END: Construct the draw object  */
    //  start drawing
    draw->Start();
    return 0;
}
