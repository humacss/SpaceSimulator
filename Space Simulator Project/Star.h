/****************************************************************************
*   FILE: Star.h
*
*   FUNCTION: This class inherits SpaceObject and is used to create
*   stars in space. Stars are different from other space objects because they
*   emit light.
*
*   PURPOSE: The star class exists to create space objects that emit light.
*
****************************************************************************/

#ifndef _Star_
#define _Star_

#include "SpaceObject.h"

class Star : public SpaceObject{
    public:
    /** Constructors    **/
    //  constructs a star with a name string, mass double, radius double,
    //  position coordinate, velocity coordinate and RGB floats
    Star(std::string, double, double,
         Coordinate, Coordinate,
         float, float, float);
    /** Getters and Setters **/
    unsigned int GetLightSource()
                    {return mLightSource;}
    void SetLightSource(unsigned int sourceId)
                    //  16384 is the integer where the glut enumerators for light
                    //  sources start
                    {mLightSource = 16384+sourceId;}
    private:
    /** Class Members   **/
    unsigned int mLightSource;
};

#endif
