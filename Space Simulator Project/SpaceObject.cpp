/****************************************************************************
*   FILE: SpaceObject.cpp
*
*   FUNCTION: This class is the base for all objects in space. All objects in
*   space have and need these properties. All objects in space are directly
*   or indirectly constructed using this class.
*
*   PURPOSE: By creating a base class for all objects in space it will be
*   easier to manage the objects in space since at least the members of this
*   class can always be accessed. This also means that it will be easier to
*   create different types of objects by just inheriting this class
*   and then adding the additional fucntionality in the new class.
*
****************************************************************************/

#include "SpaceObject.h"

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/
/**
    Name: SpaceObject(std::string, double, double,
                      Coordinate, Coordinate,
                      float, float, float)
    Function: Creates a SpaceObject with a name string, mass and radius
    doubles, position and velocit coordinates and RGB floats.
**/
SpaceObject::SpaceObject(std::string name, double mass, double radius,
                         Coordinate position, Coordinate velocity,
                         float red, float green, float blue)
{
    mName = name;
    mMass = mass;
    mRadius = radius;
    mPosition = position;
    mVelocity = velocity;
    //  force starts at neutral
    mForce = Coordinate(0, 0);
    mRed = red;
    mGreen = green;
    mBlue = blue;
}
