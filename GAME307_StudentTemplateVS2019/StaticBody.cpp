#include "StaticBody.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering)
{
	//update
	Body::Update(deltaTime);
	newOrientation(vel);

	//steering
	vel = steering->velocity;
	rotation = steering->rotation;

	//max speed
	if (VMath::mag(vel) > maxSpeed) {
		vel = VMath::normalize(vel) * maxSpeed;
	}

	//max rotation
	if (rotation > maxRotation) {
		rotation = maxRotation;
	}
}

void StaticBody::newOrientation(Vec3 velocity_) {
	if (VMath::mag(vel) > 0.0f) {
		orientation = atan2(-vel.y, vel.x);
	}
}