#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

}

Scene2::~Scene2()
{
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	IMG_Init(IMG_INIT_PNG);

	int cols = ceil(xAxis / tileWidth);
	int rows = ceil(yAxis / tileHeight);
	createTiles(rows, cols);

	Node* n = new Node(0, Vec3(8.0f, 5.2f, 0.0f));
	t = new Tile(n, 2.5f, 2.5f, this);

	graph = new Graph();
	if (!graph->onCreate(nodes)) {
		printf("graph error");
		return false;
	}

	calculateConnectionWeights();
	graph->Dijkstra(1, 5);

	return true;
}

void Scene2::createTiles(int rows, int cols)
{
	tiles.resize(rows);
	for (int i = 0; i < rows; i++) {
		tiles[i].resize(cols);
	}

	Node* n;
	Tile* t;
	int i, j, label;
	i = j = label = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight) {
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth) {

			n = new Node(label, Vec3(x, y, 0.0f));
			t = new Tile(n, tileHeight, tileWidth, this);
			n->setTile(t);
			nodes.push_back(n);
			tiles[i][j] = t;

			label++;
			j++;
		}
		j = 0;
		i++;
	}
}

void Scene2::calculateConnectionWeights()
{
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int from = tiles[i][j]->getNode()->getLabel();

			if (j > 0) {
				int to = tiles[i][j - 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			if (j < cols - 1) {
				int to = tiles[i][j + 1]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			if (i < rows - 1) {
				int to = tiles[i + 1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
			if (i > 0) {
				int to = tiles[i - 1][j]->getNode()->getLabel();
				graph->addWeightConnection(from, to, tileWidth);
			}
		}
	}
}


void Scene2::OnDestroy()
{
	for (int i = 0; i < 5; i++) {
		delete nodes[i];
		nodes[i] = nullptr;
	}
	delete graph;
	graph = nullptr;
}

void Scene2::Update(const float time)
{
}

void Scene2::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			tiles[i][j]->Render();
		}
	}

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
}
