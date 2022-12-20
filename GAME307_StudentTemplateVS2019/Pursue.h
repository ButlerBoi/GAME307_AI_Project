#ifndef PURSUE_H
#define PURSUE_H

#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

class Pursue
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;
	float time;

public:
	Pursue(Body* character_, Body* target_, float time_);
	~Pursue();
	KinematicSteeringOutput* getSteering();
};
#endif
