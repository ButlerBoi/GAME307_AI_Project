#include "Pursue.h"

Pursue::Pursue(Body* character_, Body* target_, float time_)
{
	character = character_;
	target = target_;
	time = time_;
	result = new KinematicSteeringOutput();
}

Pursue::~Pursue()
{
	if (result) { delete result; }
}

KinematicSteeringOutput* Pursue::getSteering()
{
	//Anticipate where the target will be in the future 
	//Use that point as the target for seeking
	Vec3 anticipate = target->getPos() + target->getVel() * time;
	result->velocity = anticipate - character->getPos();

	result->velocity = VMath::normalize(result->velocity);
	result->velocity = character->getMaxSpeed() * result->velocity;

	result->rotation = 0.0f;

	return result;
}
