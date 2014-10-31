/****************************************************************************
*   FILE: Draw.cpp
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

#include "Draw.h"

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/

/**
    Name: Draw(Window*, Space*, double)
    Function: Constructs a draw object by giving it a window to draw in, a
    space to draw as well as the starting scale of the window. This function
    also sets up the material and light variables to be used when drawing as
    well specifying the functions to be called by GLUT.
**/
Draw::Draw(Window* pWindow, Space* pSpace, double scaleAu)
{
    mpWindow        = pWindow;
    mpSpace         = pSpace;
    mScaleAu        = scaleAu;
    mLookAt         = mpSpace->GetObjectsInSpace();
    mLookAtIterator = mLookAt.begin();

    //  enable lighting
    const GLfloat lightAmbient[]  = {0.0, 0.0, 0.0, 1.0};
    const GLfloat lightDiffuse[]  = {1.0, 1.0, 1.0, 1.0};

    //  enable materials
    glEnable(GL_COLOR_MATERIAL);
    //  enable lighting
    glEnable(GL_LIGHTING);

    /*  START: Enable light emission from all suns   */
    //  create a copy of the list of the stars in space
    std::list<Star*> starsList = mpSpace->GetStarsInSpace();
    //  create a star list iterator
    std::list<Star*>::iterator starsIterator;
    //  iterate through the stars in space
    for(starsIterator = starsList.begin();
        starsIterator != starsList.end(); starsIterator++)
    {
        //  set a temporary emitter pointer
        Star* pStar = *starsIterator;
        if(pStar->GetLightSource())
        {
            //  enable lighting
            glEnable(pStar->GetLightSource());
            //  specify ambient lighting
            glLightfv(pStar->GetLightSource(), GL_AMBIENT,  lightAmbient);
            //  specify diffuse lighting
            glLightfv(pStar->GetLightSource(), GL_DIFFUSE,  lightDiffuse);
        }
    }
    /*  END: Enable lighting from all suns  */

    /*  START: Set materials    */
    const GLfloat matAmbient[]    = {0.7, 0.7, 0.7, 1.0};
    const GLfloat matDiffuse[]    = {0.8, 0.8, 0.8, 1.0};
    const GLfloat highShininess[] = {50.0};

    //  specify material ambient properties
    glMaterialfv(GL_FRONT, GL_AMBIENT,   matAmbient);
    //  specify diffuse properties
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   matDiffuse);
    //  specify shininess
    glMaterialfv(GL_FRONT, GL_SHININESS, highShininess);
    /*  END: Set materials  */
    //  point to my static GLUT handlers
    //  which in turn will call for my non-static handlers
    glutDisplayFunc(DisplayWrapper);
    glutIdleFunc(IdleWrapper);
    glutKeyboardFunc(KeyboardWrapper);
    glutMouseFunc(MouseWrapper);
}

/****************************************************************************
* Member Functions
*
****************************************************************************/

/**
    Name: Start()
    Function: Starts the GLUT main loop.
**/
void Draw::Start()
{
    glutMainLoop();
}

/**
    Name: DrawSphere(Coordinate, double)
    Function: Draws a sphere using the arguments radius(in screen percentage)
    and a position coordinate(that is being scaled to screen percentages
    within the function).
**/
void Draw::DrawSphere(Coordinate position, double radius)
{
    //  start new state
    glPushMatrix();
    //  set the position of the object
    glTranslated(ToScale(position.GetX()), ToScale(position.GetY()), 0.0);
    //  draw object
    glutSolidSphere(radius, 80, 80);
    //  go back to previous state
    glPopMatrix();
}

/**
    Name: DrawLighting(Star*)
    Function: Draws lighting on the argument star.
**/
void Draw::DrawLighting(Star* pStar)
{
            //  draws light positioned at the center of the star
            float gLightPosition[] = {0.0, 0.0, 1.0, 1.0};
            glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);
}

/**
    Name: DrawLighting(Planet*)
    Function: Draws lighting from all the stars in space on the argument
    planet.
**/
void Draw::DrawLighting(Planet* pPlanet)
{
    //  create a copy of the list of the stars in space
    std::list<Star*> starsList = mpSpace->GetStarsInSpace();
    //  create a star list iterator
    std::list<Star*>::iterator starsIterator;
    //  iterate through the stars in space
    for(starsIterator = starsList.begin();
        starsIterator != starsList.end(); starsIterator++)
    {
        //  set a temporary emitter pointer
        Star* pStar = *starsIterator;
        //  calculate difference in x-axis
        double x
               = pStar->GetPosition().GetX() - pPlanet->GetPosition().GetX();
        //  calculate difference in y-axis
        double y
               = pStar->GetPosition().GetY() - pPlanet->GetPosition().GetY();
        //  set the light position towards the star
        float gLightPosition[] = {x, y, 1.0, 1.0};
        glLightfv(pStar->GetLightSource(), GL_POSITION, gLightPosition);
    }
}

/**
    Name: DrawLighting(Moon*)
    Function: Draws lighting from all the stars in space on the argument
    moon.
**/
void Draw::DrawLighting(Moon* pMoon)
{
    //  create a copy of the list of the stars in space
    std::list<Star*> starsList = mpSpace->GetStarsInSpace();
    //  create a star list iterator
    std::list<Star*>::iterator starsIterator;
    //  iterate through the stars in space
    for(starsIterator = starsList.begin();
        starsIterator != starsList.end(); starsIterator++)
    {
            //  set a temporary emitter pointer
            Star* pStar = *starsIterator;
            //  calculate difference in x-axis
            float x =
               pStar->GetPosition().GetX() - pMoon->GetPosition().GetX();
            //  calculate difference in y-axis
            float y =
               pStar->GetPosition().GetY() - pMoon->GetPosition().GetY();
            //  set the light position towards the star
            float gLightPosition[] = {x, y, 1.0, 1.0};
            glLightfv(pStar->GetLightSource(), GL_POSITION, gLightPosition);
    }
}

/**
    Name: DrawStars()
    Function: Draws all the stars in space.
**/
void Draw::DrawStars()
{
    //  save a copy of the stars list
    std::list<Star*> starsList = mpSpace->GetStarsInSpace();
    //  iterate through the list
    for(std::list<Star*>::iterator starsIterator = starsList.begin();
        starsIterator != starsList.end(); starsIterator++)
    {
        //  create a temporary pointer to the current object
        Star* pStar = *starsIterator;
        //  set the colour to be used
        glColor3f(pStar->GetRed(),
                  pStar->GetGreen(),
                  pStar->GetBlue());
        //  draw the lighting on the current object
        DrawLighting(pStar);
        //  draw a sphere of the object
        DrawSphere(pStar->GetPosition(), pStar->GetRadius());
    }

}

/**
    Name: DrawPlanets()
    Function: Draws all the planets in space.
**/
void Draw::DrawPlanets()
{
    //  save a copy of the planets list
    std::list<Planet*> planetsList = mpSpace->GetPlanetsInSpace();
    //  iterate through the list
    for(std::list<Planet*>::iterator planetsIterator = planetsList.begin();
        planetsIterator != planetsList.end(); planetsIterator++)
    {
        //  create a temporary pointer to the current object
        Planet * pPlanet = *planetsIterator;
        //  set the colours to be used
        glColor3f(pPlanet->GetRed(),
                  pPlanet->GetGreen(),
                  pPlanet->GetBlue());
        //  draw the lighting on the current object
        DrawLighting(pPlanet);
        //  draw a sphere of the current object
        DrawSphere(pPlanet->GetPosition(), pPlanet->GetRadius());
    }
}

/**
    Name: DrawMoons()
    Function: Draws all the moons in space.
**/
void Draw::DrawMoons()
{
    //  save a copy of the moons list
    std::list<Moon*> moonsList = mpSpace->GetMoonsInSpace();
    //  iterate through the list
    for(std::list<Moon*>::iterator moonsIt = moonsList.begin();
        moonsIt != moonsList.end(); moonsIt++)
    {
        //  create a temporary pointer to the current object
        Moon * pMoon = *moonsIt;
        //  set the colour to be used
        glColor3f(pMoon->GetRed(),
                  pMoon->GetGreen(),
                  pMoon->GetBlue());
        //  draw the lighting on the current object
        DrawLighting(pMoon);
        //  draw a sphere of the current object
        DrawSphere(pMoon->GetPosition(), pMoon->GetRadius());
    }
}

/**
    Name: ToScale(double)
    Function: Scales the argument from meters to window percentages.
**/
double Draw::ToScale(double meters)
{
    //  One Astronomical Unit(roughly the distance between the sun and the earth)
    //  is equal to 149598e6 meters
    return (meters/(149598e6*mScaleAu));
}

/**
    Name: FromScale(double)
    Function: Scales the argument from window percentages to meters.
**/
double Draw::FromScale(double screenPercentage)
{
    return screenPercentage*149598e6*mScaleAu;
}

/**
    Name: CalculateNewObjectSpeed(int, int)
    Function: Calculates object speed on one axis, the speed being relative
    to the distance between the two int arguments(pixels) and the current
    scale.
**/
double Draw::CalculateNewObjectSpeed(int buttonDown, int buttonUp)
{
    return mScaleAu*15*(buttonUp - buttonDown);
}

/****************************************************************************
* GLUT handlers
*
****************************************************************************/

/**
    Name: Idle()
    Function: The function called when GLUT is idle.
**/
void Draw::Idle()
{
    for(int i = 0; i < 100; i++)
    {
        mpSpace->CalculateGravity();
        mpSpace->PassTime();
    }
    //  set the matrix to default
    glLoadIdentity();
    SpaceObject * pFocus = *mLookAtIterator;
    gluLookAt(
                //  the position of the eye
                ToScale(pFocus->GetPosition().GetX()),
                ToScale(pFocus->GetPosition().GetY()), 1.0,
                //  the position of the object
                ToScale(pFocus->GetPosition().GetX()),
                ToScale(pFocus->GetPosition().GetY()), 0.0,
                //  the angular rotation around the x, y, and x axises
                0, 1.0, 0);
    //  call the display function
    Display();
    //  put the application to sleep for 1 ms
    Sleep(1);
}

/**
    Name: Display()
    Function: Displays all objects in space.
**/
void Draw::Display()
{
    //  clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawStars();
    DrawPlanets();
    DrawMoons();
    //  swap the back and front buffer
    glutSwapBuffers();
}

/**
    Name: Keyboard(unsigned char, int, int)
    Function: The function for handling keyboard input. It takes in three
    arguments: The key pressed(ASCII) as well as the two mouse coordinates(pixels) when the key
    is pressed.
**/
void Draw::Keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
        /* Exits the application   */
        case 'q':
            exit(0);
            break;
        /* Zooms in    */
        case '+':
            if(mScaleAu > 0.2)
            {
                if(mScaleAu < 5)
                {
                    mScaleAu -= 0.2;
                }
                else if(mScaleAu < 1)
                {
                    mScaleAu -= 0.01;
                }
                else if(mScaleAu >= 5)
                {
                    mScaleAu--;
                }
            }
            else
            {
                //zoom in is at max
            }
            break;
        /* Zooms out   */
        case '-':
            if(mScaleAu < 30)
            {
                if(mScaleAu < 5)
                {
                    mScaleAu += 0.2;
                }
                else if(mScaleAu < 1)
                {
                    mScaleAu += 0.2;
                }
                else
                {
                    mScaleAu++;
                }
            }
            else
            {
                //zoom out is at max
            }
            break;
        /*  Look at next object in space */
        case 'n':
            //  if the end of the list isnt reached
            if(mLookAtIterator != mLookAt.end())
            {
                mLookAtIterator++;
            }
            //  if the end of the list is reached
            else
            {
                //  iterate from first object
                mLookAtIterator = mLookAt.begin();
            }
            break;
        /*  Delete last object in space */
        case 127:
            //  if looking at planet to be deleted
            if(*mLookAtIterator == mpSpace->GetObjectsInSpace().back())
            {
                //  start looking at firstobject
                mLookAtIterator = mLookAt.begin();
            }
            //  point to the last star in space
            Star* pStar = mpSpace->GetStarsInSpace().back();
            //  disable the last star in space's light emission
            glDisable(pStar->GetLightSource());
            //  deletes the last inserted object in space
            mpSpace->PopObjectFromSpace();
            //  if there are any stars in space
            if(!mpSpace->GetStarsInSpace().empty())
            {
                //  point to the last star in space
                pStar = mpSpace->GetStarsInSpace().back();
                //  enable the last star in space's light emission
                glEnable(pStar->GetLightSource());
            }
            // save the new list of objects
            mLookAt = mpSpace->GetObjectsInSpace();
            break;
    }
}

int gPosX = 0;
int gPosY = 0;

/**
    Name: Mouse(int, int, int, int)
    Function: The function for handling mouse input. Takes in an argument for
    which button pressed, the button press state(up or down) as well as
    coordinates(pixels) for the button click.
**/
void Draw::Mouse(int button, int state, int x, int y){
        switch(button)
        {
            /*  This case creates a planet at the position of the mouse.
                It also calculates the speed of the object by using
                the button release coordinates. */
            case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){
                //   rememebers the button down coordinates
                gPosX = x;
                //   rememebers the button down coordinates
                gPosY = y;
            }else if(state == GLUT_UP){
                //  create a coordinate system using half window width
                double hWidth = mpWindow->GetWidth()/2;
                //  create a coordinate system using half window height
                double hHeight = mpWindow->GetHeight()/2;
                SpaceObject * lookingAt = *mLookAtIterator;
                mpSpace->AddObjectToSpace(
                                 new Planet("Vesta", //name
                                            2.67e20, //mass
                                            0.00625 , //radius
                                            Coordinate( //position
                                               FromScale(
                                                  (gPosX-hWidth)/hWidth) +
                                                    lookingAt->
                                                       GetPosition().GetX(),
                                               FromScale(
                                                  (-gPosY+hHeight)/hHeight) +
                                                    lookingAt->
                                                       GetPosition().GetY()),
                                            Coordinate( //velocity
                                                CalculateNewObjectSpeed(
                                                   gPosX-hWidth, x-hWidth),
                                                CalculateNewObjectSpeed(
                                                  -gPosY+hWidth, -y+hWidth)),
                                            1.0, //colour red
                                            0,  //colour green
                                            0)); //colour blue
            }
            break;
        }
}

/****************************************************************************
* Getters and Setters
*
****************************************************************************/
//  define the instance
Draw * Draw::mspInstance = 0;
void Draw::SetInstance(Draw * pInstance){
    mspInstance = pInstance;
}
