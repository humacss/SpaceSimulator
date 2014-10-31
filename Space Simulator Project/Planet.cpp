/****************************************************************************
*   FILE: Planet.cpp
*
*   FUNCTION: This class inherits SpaceObject and is used to create
*   planets in space.
*
*   PURPOSE: Instead of using the SpaceObject class for constructing planets,
*   having a class dedicated for constructing planets will make it easier to
*   give planets special properties later on. This was the code will also be
*   easier to understand, since a constructed planet is a planet and a
*   SpaceObject can be any object in space, including suns and moons.
*
****************************************************************************/

#include "Planet.h"

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/

/**
    Name: Planet(std::string, double, double, Coordinate, Coordinate,
                 float, float, float)
    Function: Creates a planet with a name string, mass and radius doubles,
    position and velocity coordinates and RGB floats.
**/
Planet::Planet(
               std::string name, double mass, double radius,
               Coordinate position, Coordinate velocity,
               float red, float green, float blue){

    mName           = name;
    mMass           = mass;
    mRadius         = radius;
    mPosition       = position;
    mVelocity       = velocity;
    //  force starts at neutral
    mForce          = Coordinate(0, 0);
    mRed            = red;
    mGreen          = green;
    mBlue           = blue;
}
