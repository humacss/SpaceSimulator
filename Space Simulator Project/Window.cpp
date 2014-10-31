/****************************************************************************
*   FILE: Window.cpp
*
*   FUNCTION: The window class creates and initializes a window.
*
*   PURPOSE: Having a separate window class means it will be easier to handle
*   windows.
*
****************************************************************************/

#include "Window.h"
#include <GL/glut.h>
#include <windows.h>

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/

/**
    Name: Window(const char[], int, int, int, char**)
    Function: Constructs a window with a name char[], width and height ints,
    and forwards the int and char** main arguments
**/
Window::Window(const char pName[], int width, int height,
               int mainArgC, char* pMainArgV[]){
    mppName = &pName;
    mWidth = width;
    mHeight = height;

    mMainArgC = mainArgC;
    mppMainArgV = pMainArgV;
}

/****************************************************************************
* Class methods
*
****************************************************************************/

/**
    Name: Initialize()
    Function: Initializes the window by setting its display mode, size and
    title. Also forwards any arguments sent to the main function to GLUT(if
    constructed correctly).
**/
void Window::Initialize(){
    //  sends main arguments to GLUT
    glutInit(&mMainArgC, mppMainArgV);
    //  set the window size
    glutInitWindowSize (mWidth, mHeight);
    //  sets the display mode to:
    //  double buffers, red green blue colouring, and allows depth buffering
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //  create a window with the name argument as title
    glutCreateWindow (*mppName);
}
