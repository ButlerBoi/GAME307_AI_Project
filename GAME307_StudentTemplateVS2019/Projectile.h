#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Timer.h"
#include "Body.h"
#include "Scene.h"


class Projectile : public Body
{
private:
	Timer* mTimer;
	Scene* scene;
	float mSpeed;

public:
	Projectile();
	~Projectile();

	void Fire(Vec3 pos_);
	void Render();

};
#endif
