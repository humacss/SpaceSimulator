/****************************************************************************
*   FILE: Coordinate.h
*
*   FUNCTION: This class is made to handle coordinates in the two-dimensional
*   plane and can also perform some simple computations.
*
*   PURPOSE: To make it easier to handle coordinates within the code.
*
****************************************************************************/

#ifndef _Coordinate_
#define _Coordinate_

class Coordinate{
    public:
    /** Constructors **/
    //  default constructor
    Coordinate(){};
    //  construct a coordinate out of two x and y doubles
    Coordinate(double, double);
    /** Member Functions    **/
    //  calculates the length of the coordinate
    double          CalculateLength();
    /** Getters and Setters **/
    double          GetX(){return mX;}
    double          GetY(){return mY;}
    void            SetX(double x){mX = x;}
    void            SetY(double y){mX = y;}
    /** Operator Overloads **/
    //  adds two coordinates
    Coordinate      operator+(Coordinate);
    //  subtracts from a coordinate with another coordinate.
    Coordinate      operator-(Coordinate);
    //  multiplies a coordinate with a double
    Coordinate      operator*(double);
    //  checks if two coordinates are unequal
    bool            operator!=(Coordinate);

    private:
    /** Class members **/
    double  mX;
    double  mY;
};

#endif
