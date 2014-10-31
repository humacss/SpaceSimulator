#include "Sun.h"

Sun::Sun(
         std::string rName, double rMass, double rRadius,
         Coordinate rPosition, Coordinate rVelocity,
         float rRed, float rGreen, float rBlue, float rLight)
{
    mName           = rName;
    mMass           = rMass;
    mRadius         = rRadius;
    mPosition       = rPosition;
    mVelocity       = rVelocity;
    mForce          = Coordinate(0, 0); //force starts at neutral
    mRed            = rRed;
    mGreen          = rGreen;
    mBlue           = rBlue;
    mLight          = rLight;
}
