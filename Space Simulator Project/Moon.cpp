/****************************************************************************
*   FILE: Moon.cpp
*
*   FUNCTION: This class inherits SpaceObject and uses the distance from
*   its owner instead of position and velocity coordinates. It then
*   calculates its own velocity and position with the help of the distacne to
*   its owner.
*
*   PURPOSE: To make it easier to create moons. If owner/satellite pointers
*   are included later on it might add extra functionality to the
*   application.
*
****************************************************************************/

#include "Moon.h"
#include <math.h>

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/


/**
    Name: Moon(Planet*, std::string, double, double, double,
               float, float, float)
    Function: Creates a moon with a position and speed depending on the
    distance from its owner. Moons will always orbit their owner.
**/
Moon::Moon(Planet * pOwner, std::string name, double mass, double radius,
           double distance, float red, float green, float blue)
{
    mName = name;
    mMass = mass;
    mRadius = radius;
    //  place the moon at a certain distance from its owner
    mPosition = Coordinate(pOwner->GetPosition().GetX(),
                           pOwner->GetPosition().GetY()+distance);
    /*  START Calculate velocity    */
    //  the gravitational constant
    const double g = 6.67428e-11;
    const double PI = 3.1415926;
    //  calculating orbital period: T = 2*PI*sqrt(a*a*a/(g*M))
    //  where M is the mass of the central object and a is the distance
    double a = distance*distance*distance;
    double T = 2*PI*sqrt(a/(g*pOwner->GetMass()));
    //  calculating orbital speed: v = (a*2*PI)/T
    //  where a is the distance and T is the orbital period
    double circumference = distance*2*PI;
    double velocity = circumference/T;
    //  setting the speed
    mVelocity = Coordinate(pOwner->GetVelocity().GetX()+velocity,
                           pOwner->GetVelocity().GetY());
    /*  END Calculate velocity  */
    //  force starts at neutral
    mForce = Coordinate(0, 0);
    mRed = red;
    mGreen = green;
    mBlue = blue;
}
