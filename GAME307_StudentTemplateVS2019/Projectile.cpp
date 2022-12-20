#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Fire(Vec3 pos_)
{
	pos = pos_;
}

void Projectile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	SDL_Rect rect;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}
