#include "Mya.h"

bool Mya::run = NULL;
bool Mya::fullscreen = NULL;
Assets* Mya::assets = NULL;
Lua* Mya::lua = NULL;

Mya::Mya() {
	renderer = nullptr;
	window = nullptr;
}

void Mya::initLua() {
	lua = new Lua();
	lua->loadMya(this);
	lua->loadGraphics();
	lua->loadNetwork();
	lua->loadAudio();
	lua->loadCol(); //Colonialist Game Assets
}

bool Mya::init(std::string title, int w, int h) {
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		std::cout << "Error IN Mya::init, with SDL_Init: " << SDL_GetError() << std::endl;
		run = false;
	}
	else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error IN Mya::init, with IMG_Init: " << IMG_GetError() << std::endl;
		run = false;
	}
	else if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize!SDL_ttf Error : %s\n", TTF_GetError());
		run = false;
	}
	else if (SDLNet_Init() == -1) {
		printf("SDLNet could not initialize!SDLNet Error : %s\n", SDLNet_GetError());
		run = false;
	}
	else {
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		//GPU_SetInitWindow(SDL_GetWindowID(window));
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
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);//I like this grey. Fucking fight me bish.
					SDL_UpdateWindowSurface(window);

					SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

					assets = new Assets(this);
					//lua->lua["assets"] = assets;

					timepertick = 1000 / ups;
					timer = std::clock();
					SDL_StartTextInput();
					std::cout << "Sucessfully started " << VERSION << "!" << std::endl;
					
					run = true;
				}
			}
		}
	}
	return run;
}

void Mya::update() {
	overall += (std::clock() - timer);
	while (overall >= timepertick) {
		overall -= timepertick;
		lua->exec("if event_tupdate ~= nil then event_tupdate() end");
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
			char k = 0;

			k = e.key.keysym.sym;
			sol::function event_keyDown = lua->lua["event_keyDown"];
			if (event_keyDown != sol::nil) {
				if (k == SDLK_ESCAPE)
					event_keyDown("esc");
				else if (k == SDLK_BACKSPACE)
					event_keyDown("backspace");
				else if (k == SDLK_KP_ENTER)
					event_keyDown("enter");
				else
					event_keyDown(k);
			}
			else
				std::cout << "event_keyDown not registered\n";
		}
		if (e.type == SDL_KEYUP) {
			char k = 0;

			k = e.key.keysym.sym;

			sol::function event_keyDown = lua->lua["event_keyUp"];
			if (event_keyDown != sol::nil) {
				if (k == SDLK_ESCAPE) 
					event_keyDown("esc");
				else if (k == SDLK_BACKSPACE)
					event_keyDown("backspace");
				else if (k == SDLK_KP_ENTER)
					event_keyDown("enter");
				else
					event_keyDown(k);
			}
			else
				std::cout << "event_keyUp not registered\n";
		}
		if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
				//lua->exec("if event_windowResize ~= nil then event_windowResize(" + std::to_string(SCREEN_WIDTH) + "," + std::to_string(SCREEN_HEIGHT) + ") end");
				
				sol::function event_keyDown = lua->lua["event_windowResize"];
				if (event_keyDown != sol::nil)
					event_keyDown(SCREEN_WIDTH, SCREEN_HEIGHT);
				else
					std::cout << "event_windowResize not registered\n";
			}
		if (e.type == SDL_MOUSEMOTION) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			lua->exec("if event_mouseMotion ~= nil then event_mouseMotion(" + std::to_string(x) + "," + std::to_string(y) + ") end");
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

			sol::function event_mouseButtonDown = lua->lua["event_mouseButtonDown"];
			if (event_mouseButtonDown != sol::nil)
				event_mouseButtonDown(k);
			else
				std::cout << "event_mouseButtonDown not registered\n";
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

			sol::function event_mouseButtonDown = lua->lua["event_mouseButtonUp"];
			if (event_mouseButtonDown != sol::nil)
				event_mouseButtonDown(k);
			else
				std::cout << "event_mouseButtonUp not registered\n";
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			
		}
		if (e.type == SDL_MOUSEWHEEL) {
			
		}
	}

	lua->exec("if event_update ~= nil then event_update() end");
}

void Mya::render() {
	SDL_SetRenderDrawColor(renderer, 45, 45, 48, 0);
	fps.frames++;
	SDL_RenderClear(renderer);

	lua->exec("if event_render ~= nil then event_render() end");

	SDL_RenderPresent(renderer);
}

void Mya::exit() {
	lua->exec("if event_quit ~= nil then event_quit() end");
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
	SDLNet_Quit();
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
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FOREIGN);
		SDL_SetWindowSize(window, osw, osh);
		SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	}
	fullscreen = b;

	sol::function event_keyDown = lua->lua["event_windowResize"];
	if (event_keyDown != sol::nil)
		event_keyDown(SCREEN_WIDTH, SCREEN_HEIGHT);
	else
		std::cout << "event_windowResize not registered\n";
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
	std::string p = SDL_GetBasePath()+tex;
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
	return (std::string)SDL_GetBasePath();
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
