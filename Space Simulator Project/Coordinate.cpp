/****************************************************************************
*   FILE: Coordinate.cpp
*
*   FUNCTION: This class is made to handle coordinates in the two-dimensional
*   plane and can also perform some simple computations.
*
*   PURPOSE: To make it easier to handle coordinates within the code.
*
****************************************************************************/

#include "Coordinate.h"
#include <math.h>

/****************************************************************************
 * Constructors
 *
 ***************************************************************************/

/**
    Name: Coordinate(double, double)
    Function: Constructs a coordinate out of two doubles.
**/
Coordinate::Coordinate(double x, double y)
{
    mX = x;
    mY = y;
}

/****************************************************************************
* Member Functions
*
****************************************************************************/

/**
    Name: CalculateLength()
    Function: Caluclates the length of a coordinate as a straight line from
    origin.
**/
double Coordinate::CalculateLength()
{
    return sqrt(mX*mX + mY*mY);
}

/****************************************************************************
* Operator Overloads
*
****************************************************************************/

/**
    Name: operator+(Coordinate)
    Function: Adds two coordinates.
**/
Coordinate Coordinate::operator+(Coordinate toAdd)
{
    return Coordinate(mX+toAdd.GetX(),mY+toAdd.GetY());
}

/**
    Name: operator-(Coordinate)
    Function: Subtracts from a coordinate with another coordinate.
**/
Coordinate Coordinate::operator-(Coordinate toSubtract)
{
    return Coordinate(mX-toSubtract.GetX(),mY-toSubtract.GetY());
}

/**
    Name: operator*(double)
    Function: Multiplies a coordinate with a double.
**/
Coordinate Coordinate::operator*(double toMultiply)
{
    return Coordinate(mX*toMultiply,mY*toMultiply);
}

/**
    Name: operator!=(Coordinate)
    Function: Checks if two coordinates are unequal.
**/
bool Coordinate::operator!=(Coordinate toCompare)
{
    if(mX == toCompare.GetX() && mY == toCompare.GetY())
        return false;
    else
        return true;
}
