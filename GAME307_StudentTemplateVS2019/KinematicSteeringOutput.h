#ifndef KINEMATICSTEERINGOUTPUT_H
#define KINEMATICSTEERINGOUTPUT_H

#include "Vector.h"
using namespace MATH;

class KinematicSteeringOutput {
public:
	Vec3 velocity;
	float rotation;

	KinematicSteeringOutput();
	KinematicSteeringOutput(Vec3 velocity_, float rotation_);
};
#endif