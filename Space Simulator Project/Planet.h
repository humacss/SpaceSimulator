/****************************************************************************
*   FILE: Planet.h
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

#ifndef _Planet_
#define _Planet_
#include "SpaceObject.h"

class Planet : public SpaceObject{
    public:
    /** Constructors    **/
    //  constructs a planet with a name string, mass and radius doubles,
    //  position and velociy coordinates and RGB floats
    Planet(std::string, double, double,
           Coordinate, Coordinate,
           float, float, float);
};
#endif
