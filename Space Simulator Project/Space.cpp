/****************************************************************************
*   FILE: Space.cpp
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

#include "Space.h"

/****************************************************************************
* Constructors
*
****************************************************************************/

/**
    Name: Space(int)
    Function: Constructs a Space with the integer time given as time to pass
    in PassTime().
**/
Space::Space(int time){
    mTime = time;
}

/****************************************************************************
* Member Functions
*
****************************************************************************/

/**
    Name: AddObjectToSpace(Planet*)
    Function: Adds an object to the ObjectsInSpace list and the
    PlanetsInSpace list.
**/
void Space::AddObjectToSpace(Planet* pPlanet){
    mObjectsInSpace.push_back(pPlanet);
    mPlanetsInSpace.push_back(pPlanet);
}

/**
    Name: AddObjectToSpace(Moon*)
    Function: Adds an object to the ObjectsInSpace list and the
    MoonsInSpace list.
**/
void Space::AddObjectToSpace(Moon* pMoon){
    mObjectsInSpace.push_back(pMoon);
    mMoonsInSpace.push_back(pMoon);
}

/**
    Name: AddObjectToSpace(Star*)
    Function: Adds an object to the ObjectsInSpace list and the
    StarsInSpace list.
**/
void Space::AddObjectToSpace(Star* pStar){
    mObjectsInSpace.push_back(pStar);
    //  if there are less than 9 stars
    //  GLUT can only handle up to 8 light sources
    if(mStarsInSpace.size() < 9){
        pStar->SetLightSource(mStarsInSpace.size());
    }
    mStarsInSpace.push_back(pStar);

}

/**
    Name: PopObjectFromSpace()
    Function: Removes the last object from the ObjectsInSpace and the
    Star/Planet/Moon list depending on its type and frees the objects
    allocated memory.
**/
void Space::PopObjectFromSpace(){
    //  if there are objects in space
    if(!mObjectsInSpace.empty())
    {
        //  set a temp pointer to the last object in space
        SpaceObject* pLastObject = mObjectsInSpace.back();
        //  if there are stars in space
        if(!mStarsInSpace.empty())
        {
            //  set a temporary pointer to the last star in space
            Star* star = mStarsInSpace.back();
            //  if mass of star = mass of spaceobject
            if(pLastObject->GetMass() == star->GetMass() && star != 0)
            {
                //  remove the star from the list of stars
                mStarsInSpace.pop_back();
            }
        }
        //  if there are planets in space
        if(!mPlanetsInSpace.empty())
        {
            //  set a temporary pointer to the last planet in space
            Planet* planet = mPlanetsInSpace.back();
            //  if mass of planet = mass of spaceobject
            if(pLastObject->GetMass() == planet->GetMass())
            {
                //  remove the planet from the list of planets
                mPlanetsInSpace.pop_back();
            }
        }
        //  if there are moons in space
        if(!mMoonsInSpace.empty())
        {
            //  set a temporary pointer to the last moon in space
            Moon* moon = mMoonsInSpace.back();
            //  if mass of moon = mass of spaceobject
            if(pLastObject->GetMass() == moon->GetMass())
            {
                //  remove the moon from the list of moons
                mMoonsInSpace.pop_back();
            }
        }
        //  remove the last object from the list of objects
        mObjectsInSpace.pop_back();
        //  free the memory allocated by the object
        delete pLastObject;
    //  if the list is empty
    }else
    {
        //handle error
    }
}

/**
    Name: CalculateGravity()
    Function: Calculates gravity between all elements in ObjectsInSpace.
**/
void Space::CalculateGravity(){
    std::list<SpaceObject*>::iterator it;
    std::list<SpaceObject*>::iterator it2;
    SpaceObject * Object1;
    SpaceObject * Object2;
    //  iterate through the list
    for( it = mObjectsInSpace.begin(); it != mObjectsInSpace.end(); it++)
    {
        it2 = it;
        //  iterate one step ahead of the previous for
        for(it2++; it2 != mObjectsInSpace.end(); it2++)
        {
            Object1 = *it;
            Object2 = *it2;
            //  the universal gravitational constant
            const double g = 6.67428e-11;
            //  calculate the distance between the two objects
            Coordinate distance =
                Object2->GetPosition() - Object1->GetPosition();
            //  calculate the lentgh of the distance
            double length = distance.CalculateLength();
            //  calculate the gravitational pull between the objects:
            //  F = (G*m1*m2)/r*r where r is the length of the distance.
            double force =
                ((g*Object1->GetMass()*Object2->GetMass())/(length*length));
            distance = distance*(1/length);
            distance = distance*force;
            //  set the gravitational force to object1
            Object1->SetForce(Object1->GetForce()+distance);
            //  set the gravitational force to object2
            Object2->SetForce(Object2->GetForce()-distance);
        }
    }

}

/**
    Name: PassTime()
    Function: Calculates the new positions for all objects in space after a
    certain amount of time has passed.
**/
void Space::PassTime(){
    std::list<SpaceObject*>::iterator it;
    //  iterate through the list of objects in space
    for( it = mObjectsInSpace.begin(); it != mObjectsInSpace.end(); it++)
    {
        //  point to the current object
        SpaceObject * pObject = *it;
        //  if mass isnt zero. Reason: There is a division by mass later on.
        if(pObject->GetMass() != 0)
        {
            //  update position with current velocity
            pObject->SetPosition(pObject->GetPosition() +
                                 (pObject->GetVelocity() * mTime));
            //  calculate acceleration using the current force
            Coordinate acceleration = Coordinate(pObject->GetForce() *
                                                 (1/pObject->GetMass()));
            //  set new position using the acceleration
            pObject->SetPosition(pObject->GetPosition() +
                                 ((acceleration)*(mTime*mTime)*0.5));
            //  set the new velocity using the acceleration
            pObject->SetVelocity(pObject->GetVelocity() +
                                 acceleration*mTime);
            //  the calculation is finished so force is set to 0
            pObject->SetForce(Coordinate(0, 0));
        }
        else
        {
            //handle error
        }

    }
}
