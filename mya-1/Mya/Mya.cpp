#include "Mya.h"

bool Mya::run = NULL;
bool Mya::fullscreen = NULL;
Assets* Mya::assets = NULL;

Mya::Mya() {
	renderer = nullptr;
	window = nullptr;
}

bool Mya::init(std::string title, int w, int h) {
	std::cout << "Initializing Mya...\n";
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		std::cout << "Error IN Mya::init, with SDL_Init: " << SDL_GetError() << std::endl;
		run = false;
	} else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error IN Mya::init, with IMG_Init: " << IMG_GetError() << std::endl;
		run = false;
	} else if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize!SDL_ttf Error : %s\n", TTF_GetError());
		run = false;
	} else {
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			std::cout << "Error IN Mya::init, with SDL_CreateWindow: " << SDL_GetError() << std::endl;
			run = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer) {
				std::cout << "Error IN Mya::init, with SDL_CreateRenderer: " << SDL_GetError() << std::endl;
				run = false;
			}
			else {
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					run = false;
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//I like this grey. Fucking fight me bish.
					SDL_UpdateWindowSurface(window);

					SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

					assets = new Assets(this);

					timepertick = 1000 / ups;
					timer = std::clock();
					SDL_StartTextInput();
					tv = new TextView(Font("assets/font.ttf", 64), "Hai", 0, 0, renderer);
					
					assets->loadTexture("logo", "assets/art/art_logo.png");
					sprite = new Sprite(assets->getTexture("logo"));
					sprite->x = 0;
					sprite->y = 0;
					sprite->w = 100;
					sprite->h = 100;

					lua = new Lua();
					lua->loadMya(this);
					lua->loadGraphics();
					lua->loadAudio();
					
					std::cout << "Sucessfully started " << VERSION << "!" << std::endl;
					
					run = true;
				}
			}
		}
	}
	return run;
}

bool Mya::loop()
{
	update();
	render();
	return isRunning();
}

void Mya::update() {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
	}
	timer = std::clock();

	deltaTimer.start();
	SDL_Event e;

	fps.update();
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			exit();
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_KEYUP) {
		}
		if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
			}
		if (e.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			std::string k = "null";

			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				k = "left";
				break;
			case SDL_BUTTON_RIGHT:
				k = "right";
				break;
			case SDL_BUTTON_MIDDLE:
				k = "middle";
				break;
			case SDL_BUTTON_X1:
				k = "mouse4";
				break;
			case SDL_BUTTON_X2:
				k = "mouse5";
				break;
			default:
				k = "null";
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			std::string k = "null";

			switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					k = "left";
					break;
				case SDL_BUTTON_RIGHT:
					k = "right";
					break;
				case SDL_BUTTON_MIDDLE:
					k = "middle";
					break;
				case SDL_BUTTON_X1:
					k = "mouse4";
					break;
				case SDL_BUTTON_X2:
					k = "mouse5";
					break;
				default:
					k = "null";
					break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			
		}
		if (e.type == SDL_MOUSEWHEEL) {

		}
	}
}

void Mya::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	fps.frames++;
	SDL_RenderClear(renderer);

	sprite->render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	tv->setText("FPS: " + std::to_string(fps.fps), renderer);
	tv->render(renderer);

	SDL_RenderPresent(renderer);
}

void Mya::exit() {
	run = false;
}

bool Mya::isRunning() {
	return run;
}

void Mya::close() {
	std::cout << "close" << std::endl;
	SDL_StopTextInput();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Mya::setFullscreen(bool b) {
	if (b) {
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		osw = getWidth();
		osh = getHeight();
		SDL_SetWindowSize(window, DM.w, DM.h);
		SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
		//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	} else {
		//SDL_SetWindowFullscreen(window, SDL_WINDOW_FOREIGN);
		SDL_SetWindowSize(window, osw, osh);
		SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	}
	fullscreen = b;
}

bool Mya::getFullscreen() {
	return fullscreen;
}

SDL_Window* Mya::getWindow() {
	return window;
}

SDL_Renderer* Mya::getRenderer() {
	return renderer;
}

void Mya::setWindowTitle(std::string text){
	SDL_SetWindowTitle(window, text.c_str());
}

void Mya::setWindowIcon(std::string tex) {
	std::string p = "" + tex;
	SDL_SetWindowIcon(window, IMG_Load(p.c_str()));
}

void Mya::showCursor(bool a) {
	SDL_ShowCursor(a);
}

int Mya::getWidth()
{
	return SCREEN_WIDTH;
}

int Mya::getHeight()
{
	return SCREEN_HEIGHT;
}

std::string Mya::getPath()
{
	return "";
}

void Mya::setRenderDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Mya::setIsOnTop(bool onTop){
	SDL_SetWindowGrab(window, (SDL_bool) onTop);
}

std::string Mya::getVersion() {
	return VERSION;
}

int Mya::getFps() {
	return fps.fps;
}

bool Mya::getIsServer() {
	return isServer;
}

Assets* Mya::getAssets() {
	return assets;
}

void Mya::setUPS(int u)
{
	ups = u;
	timepertick = 1000 / u;
}

int Mya::getUPS()
{
	return ups;
}

void Mya::deltaUpdate()
{
	if (!trueDeltaTimer.isStarted())
		trueDeltaTimer.start();
	else {
		delta = trueDeltaTimer.getTicks();
		trueDeltaTimer.stop();
		trueDeltaTimer.start();
	}
}

float Mya::getDelta()
{
	return delta;
}

void* Mya::lua_getRenderer() {
	return (void*) renderer;
}

Mya* Mya::getMya() {
	return this;
}
