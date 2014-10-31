/****************************************************************************
*   FILE: SpaceObject.h
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

#ifndef _SpaceObject_
#define _SpaceObject_

#include "Coordinate.h"
#include <string>

class SpaceObject{
    public:
    /** Constructors    **/
    //  default constructor
    SpaceObject(){};
    //  creates a SpaceObject with a name string, mass and radius
    //  doubles, position and velocit coordinates and RGB floats.
    SpaceObject(std::string, double, double, Coordinate, Coordinate, float,
                float, float);
    /** Getters and Setters **/
    std::string         GetName()
                            {return mName;}
    void                SetName(std::string name)
                            {mName = name;}
    double              GetRadius()
                            {return mRadius;}
    void                SetRadius(double radius)
                            {mRadius = radius;}
    double              GetMass()
                            {return mMass;}
    void                SetMass(double mass)
                            {mMass = mass;}
    Coordinate          GetPosition()
                            {return mPosition;}
    void                SetPosition(Coordinate position)
                            {mPosition = position;}
    Coordinate          GetVelocity()
                            {return mVelocity;}
    void                SetVelocity(Coordinate velocity)
                            {mVelocity = velocity;}
    Coordinate          GetForce()
                            {return mForce;}
    void                SetForce(Coordinate force)
                            {mForce = force;}
    float               GetRed()
                            {return mRed;}
    float               GetGreen()
                            {return mGreen;}
    float               GetBlue()
                            {return mBlue;}
    void                SetColour(float red, float green, float blue)
                            {mRed = red; mGreen = green; mBlue = blue;}

    protected:
    /** Class Members   **/
    std::string         mName;
    double              mRadius;
    double              mMass;
    Coordinate          mPosition;
    Coordinate          mVelocity;
    Coordinate          mForce;
    float               mRed;
    float               mGreen;
    float               mBlue;
};

#endif
