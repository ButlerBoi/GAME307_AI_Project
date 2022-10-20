#ifndef KINEMATICFLEE_H
#define KINEMATICFLEE_H

#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicFlee
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;

public:
	KinematicFlee(Body* character_, Body* target_);
	~KinematicFlee();
	KinematicSteeringOutput* getSteering();
};

#endif
