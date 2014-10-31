/****************************************************************************
*   FILE: Moon.h
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

#ifndef _Moon_
#define _Moon_

#include "Planet.h"
#include "SpaceObject.h"

class Moon : public SpaceObject{
    public:
    /** Constructors    **/
    //  constructs a moon with a name string, mass, radius and distance
    //  doubles as well as RGB floats
    Moon(Planet*, std::string, double, double,
         double,
         float, float, float);
};
#endif
