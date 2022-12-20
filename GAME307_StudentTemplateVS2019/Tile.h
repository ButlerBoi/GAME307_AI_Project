#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>

#include "Node.h"
#include "Scene.h"

class Tile
{
private:
	Node* node;
	float width;
	float height;
	Uint8 r, g, b, a;
	Scene* scene;

	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}
public:
	Tile(Node* node_, float height_, float width_, Scene* scene_) {
		node = node_;
		height = height_;
		width = width_;
		r = 100;
		g = 150;
		b = 0;
		a = 255;
		scene = scene_;
	}
	~Tile(){}
	void Render();
	Node* getNode() { return node; }
};
#endif
