#ifndef _Sun_
#define _Sun_

#include "SpaceObject.h"

class Sun : public SpaceObject{
    private:
    float mLight;
    public:
    Sun(){};
    Sun(std::string, double, double, Coordinate, Coordinate, float, float, float, float);

};

#endif
