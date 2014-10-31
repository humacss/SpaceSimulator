/****************************************************************************
*   FILE: Star.cpp
*
*   FUNCTION: This class inherits SpaceObject and is used to create
*   stars in space. Stars are different from other space objects because they
*   emit light.
*
*   PURPOSE: The star class exists to create space objects that emit light.
*
****************************************************************************/

#include "Star.h"

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/

/**
    Name: Star(std::string, double, double, Coordinate, Coordinate,
                 float, float, float)
    Function: Creates a star with a name string, mass and radius doubles,
    position and velocity coordinates and RGB floats.
**/
Star::Star(
         std::string name, double mass, double radius,
         Coordinate position, Coordinate velocity,
         float red, float green, float blue)
{
    mName           = name;
    mMass           = mass;
    mRadius         = radius;
    mPosition       = position;
    mVelocity       = velocity;
    mForce          = Coordinate(0, 0); //force starts at neutral
    mRed            = red;
    mGreen          = green;
    mBlue           = blue;
}
