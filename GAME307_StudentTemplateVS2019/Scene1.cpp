#include "Scene1.h"
#include "VMath.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	blinky = nullptr;
	seekNPC = NULL;
}

Scene1::~Scene1(){
	if (blinky) 
	{
		blinky->OnDestroy();
		delete blinky;
	}
	if (steering) 
	{
		steering = nullptr;
		delete blinky;
	}
	if (seekAlgorithm) 
	{
		seekAlgorithm = nullptr;
		delete seekAlgorithm;
	}
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this))
	{
		return false;
	}

	image = IMG_Load("Blinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		blinky->setTexture(texture);
		SDL_FreeSurface(image);
	}
	
	Vec3 position = Vec3();
	float orientation = 0.0f;
	float maxSpeed = 2.5f;
	float maxRotation = 1.0f;
	seekNPC = new StaticBody(position, orientation, maxSpeed, maxRotation);

	Vec3 position2 = Vec3(15.0f, 5.0f, 0.0f);
	float orientation2 = 0.0f;
	float maxSpeed2 = 1.5f;
	float maxRotation2 = 1.0f;
	fleeNPC = new StaticBody(position2, orientation2, maxSpeed2, maxRotation2);


	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		seekNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	image = IMG_Load("Pinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		fleeNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	// end of character set ups
	player = game->getPlayer();

	fleeAlgorithm = new KinematicFlee(fleeNPC, player);

	seekAlgorithm = new KinematicSeek(seekNPC, player);



	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);

	steering = seekAlgorithm->getSteering();
	fleeing = fleeAlgorithm->getSteering();

	seekNPC->Update(deltaTime, steering);

	fleeNPC->Update(deltaTime, fleeing);
	
	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	//blinky->render(0.15f);

	SDL_Rect square;
	SDL_Rect square2;
	Vec3 screenCoords;
	Vec3 screenCoords2;
	int w, h;
	float scale = 0.15f;

	SDL_QueryTexture(seekNPC->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * seekNPC->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;
	float orientation = seekNPC->getOrientation() * 180 / M_PI;

	SDL_RenderCopyEx(renderer, seekNPC->getTexture(), nullptr, &square, orientation, nullptr, SDL_FLIP_NONE);

	SDL_QueryTexture(fleeNPC->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords2 = projectionMatrix * fleeNPC->getPos();
	square2.x = static_cast<int>(screenCoords2.x - 0.5f * w);
	square2.y = static_cast<int>(screenCoords2.y - 0.5f * h);
	square2.w = w;
	square2.h = h;
	float orientation2 = fleeNPC->getOrientation() * 180 / M_PI;
	SDL_RenderCopyEx(renderer, fleeNPC->getTexture(), nullptr, &square2, orientation2, nullptr, SDL_FLIP_NONE);



	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
