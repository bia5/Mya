#include "Mya.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

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
}

bool Mya::init(std::string title, int w, int h) {
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
#ifdef __EMSCRIPTEN__
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
#else
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK)) {
#endif
		std::cout << "Error IN Mya::init, with SDL_Init: " << SDL_GetError() << std::endl;
		run = false;
	} else if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "Error IN Mya::init, with IMG_Init: " << IMG_GetError() << std::endl;
		run = false;
	} else if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize!SDL_ttf Error : %s\n", TTF_GetError());
		run = false;
	} else if (SDLNet_Init() == -1) {
		printf("SDLNet could not initialize!SDLNet Error : %s\n", SDLNet_GetError());
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

#ifndef __EMSCRIPTEN__
					//Add joystick
					if (!joystick) {
						std::cout << "Searching for joysticks\n";
						for (int i = 0; i < SDL_NumJoysticks(); i++) {
							joystick = SDL_JoystickOpen(i);

							if (joystick) {
								std::cout << "Joystick found: " << i << ", name: ";
								printf("%s\n", SDL_JoystickName(joystick));
								break;
							}
							else
								std::cout << "Error IN Mya::init, with SDL_GameControllerOpen: " << SDL_GetError() << std::endl;
						}
					}

					if (!joystick)
						std::cout << "No joystick found.\n";
#endif

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
	if (overall >= timepertick) {
		overall -= timepertick;
		lua->exec("if event_tupdate ~= nil then event_tupdate() end");
	}
	timer = std::clock();

	deltaTimer.start();
	SDL_Event e;


#ifndef __EMSCRIPTEN__
	if(SDL_JoystickGetButton(joystick, 0)) {
		std::cout << "Button 0 pressed" << std::endl;
	}
#endif

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
				if (e.key.keysym.sym == SDLK_LSHIFT)
					event_keyDown("LSHIFT");
				else if (e.key.keysym.sym == SDLK_RSHIFT)
					event_keyDown("RSHIFT");
				else
					event_keyDown(SDL_GetKeyName(k));
			} else
				std::cout << "event_keyDown not registered\n";
		}
		if (e.type == SDL_KEYUP) {
			char k = 0;

			k = e.key.keysym.sym;

			sol::function event_keyDown = lua->lua["event_keyUp"];
			if (event_keyDown != sol::nil) {
				if (e.key.keysym.sym == SDLK_LSHIFT)
					event_keyDown("LSHIFT");
				else if (e.key.keysym.sym == SDLK_RSHIFT)
					event_keyDown("RSHIFT");
				else
					event_keyDown(SDL_GetKeyName(k));
			} else
				std::cout << "event_keyUp not registered\n";
		}
		if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
				
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

#ifndef __EMSCRIPTEN__
		if (e.type == SDL_JOYDEVICEADDED) {
			std::cout << "Joystick inserted: " << e.jdevice.which << "\n";
			
			if (!joystick) {
				std::cout << "Searching for joysticks\n";
				for (int i = 0; i < SDL_NumJoysticks(); i++) {
					joystick = SDL_JoystickOpen(i);

					if (joystick) {
						std::cout << "Joystick found: " << i << ", name: ";
						printf("%s\n", SDL_JoystickName(joystick));
						break;
					}
					else
						std::cout << "Error IN Mya::init, with SDL_GameControllerOpen: " << SDL_GetError() << std::endl;
				}
			}
		}
		if (e.type == SDL_JOYDEVICEREMOVED) {
			std::cout << "Joystick removed: " << e.jdevice.which << "\n";
			joystick = NULL;
			
			if (!joystick) {
				std::cout << "Searching for joysticks\n";
				for (int i = 0; i < SDL_NumJoysticks(); i++) {
					joystick = SDL_JoystickOpen(i);

					if (joystick) {
						std::cout << "Joystick found: " << i << ", name: ";
						printf("%s\n", SDL_JoystickName(joystick));
						break;
					}
					else
						std::cout << "Error IN Mya::init, with SDL_GameControllerOpen: " << SDL_GetError() << std::endl;
				}
			}
		}
#endif
	}

	lua->exec("if event_update ~= nil then event_update() end");
}

void Mya::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	fps.frames++;
	SDL_RenderClear(renderer);
	
	lua->exec("if event_render ~= nil then event_render() end");

	SDL_RenderPresent(renderer);

#ifdef __EMSCRIPTEN__
	emscripten_sleep(0);
#endif
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
	} else {
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
#ifdef __EMSCRIPTEN__
	std::string p = "" + tex;
#else
	std::string p = SDL_GetBasePath() + tex;
#endif
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
#ifdef __EMSCRIPTEN__
	return "";
#else
	return (std::string)SDL_GetBasePath();
#endif
}

void Mya::setRenderDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Mya::setIsOnTop(bool onTop){
	SDL_SetWindowGrab(window, (SDL_bool) onTop);
}

std::string Mya::getPlatform()
{
	return PLATFORM;
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
