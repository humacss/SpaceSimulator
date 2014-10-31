/****************************************************************************
*   FILE: Space.h
*
*   FUNCTION: This class manages a space and all objects within it. It is the
*   class that calculates gravity between all objects and is also the class
*   that updates their positions depending on their speed and direction.
*
*   PURPOSE: The space class makes handling spaces and the objects within
*   it much easier and will also make it easier to use multiple spaces if
*   this is supported in the future.
*
****************************************************************************/

#ifndef _Space_
#define _Space_

#include "SpaceObject.h"
#include "Star.h"
#include "Planet.h"
#include "Moon.h"
#include <list>

class Space{
    public:
    /** Constructors    **/
    //  constructs a space with the given integer as the amount of seconds to
    //  update when updating
    Space(int);
    /** Member Functions   **/
    //  adds a planet to the objects and planets lists
    void                        AddObjectToSpace(Planet*);
    //  adds a star to the objects and stars lists
    void                        AddObjectToSpace(Star*);
    //  adds a moon to the objects and moons lists
    void                        AddObjectToSpace(Moon*);
    //  removes the last element created
    void                        PopObjectFromSpace();
    //  calculates gravity between all elements in the objects list
    void                        CalculateGravity();
    //  calculates new positions for all elements in the objects list after a
    //  certain amount of time has passed
    void                        PassTime();
    /** Getters and Setters **/
    std::list<SpaceObject *>    GetObjectsInSpace()
                                    {return mObjectsInSpace;}
    std::list<Star *>           GetStarsInSpace()
                                    {return mStarsInSpace;}
    std::list<Planet *>         GetPlanetsInSpace()
                                    {return mPlanetsInSpace;}
    std::list<Moon *>           GetMoonsInSpace()
                                    {return mMoonsInSpace;}
    int                         GetTime()
                                    {return mTime;};
    void                        SetTime(int time)
                                    {mTime = time;}

    private:
    /** Class Members   **/
    std::list<SpaceObject *>    mObjectsInSpace;
    std::list<Planet *>         mPlanetsInSpace;
    std::list<Star *>           mStarsInSpace;
    std::list<Moon *>           mMoonsInSpace;
    int                         mTime;

};

#endif
