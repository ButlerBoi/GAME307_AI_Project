#include "KinematicFlee.h"

KinematicFlee::KinematicFlee(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicFlee::~KinematicFlee()
{
	if (result) { delete result; }
}

KinematicSteeringOutput* KinematicFlee::getSteering()
{
	result->velocity = character->getPos() - target->getPos();

	//full speed along this direction
	result->velocity = VMath::normalize(result->velocity);
	result->velocity = character->getMaxSpeed() * result->velocity;

	result->rotation = 0.0f;


	return result;
}
