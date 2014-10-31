/****************************************************************************
*   FILE: Window.h
*
*   FUNCTION: The window class creates and initializes a window.
*
*   PURPOSE: Having a separate window class means it will be easier to handle
*   windows.
*
****************************************************************************/

#ifndef _Window_
#define _Window_

#include <string>

class Window{
    public:
    /** Constructors    **/
    //  constructs a window with a name char[], width and height ints,
    //  and forwards the int and char** main arguments
    Window(const char[], int, int, int, char**);
    /** Member Functions   **/
    //  initializes a window with the arguments given at construction
    void            Initialize();
    /** Getters and Setters **/
    int             GetWidth()
                        {return mWidth;}
    void            SetWidth(int width)
                        {mWidth = width;}
    int             GetHeight()
                        {return mHeight;}
    void            SetHeight(int height)
                        {mHeight = height;}

    private:
    /** Class Members   **/
    const char**    mppName;
    int             mWidth;
    int             mHeight;
    int             mMainArgC;
    char **         mppMainArgV;
};
#endif
