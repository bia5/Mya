#include "Mya.h"

char __BUILD_NUMBER;

Mya::Mya(){
	std::cout << "Build Number: " << +__BUILD_NUMBER << "\n";
	VERSION = "Mya v"+std::to_string(VERSION_PRIMARY)+"."+std::to_string(VERSION_SECONDARY)+"."+std::to_string(VERSION_TERTIARY)+" "+VERSION_CODENAME;
	std::cout << "Launching "+VERSION+"!\n";
	SDL_Init(SDL_INIT_EVERYTHING);
}

bool Mya::initGraphics(){
	if(SDL_Init(SDL_INIT_EVERYTHING) > -1){
		window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(window != NULL){
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = WINDOW_NAME.c_str();
			appInfo.applicationVersion = VK_MAKE_VERSION(APP_VERSION_PRIMARY, APP_VERSION_SECONDARY, APP_VERSION_TERTIARY);
			appInfo.pEngineName = VERSION.c_str();
			appInfo.engineVersion = VK_MAKE_VERSION(VERSION_PRIMARY, VERSION_SECONDARY, VERSION_TERTIARY);
			appInfo.apiVersion = VK_API_VERSION_1_2;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;
			//Copied from SDL's website
			uint32_t extensionCount;
			SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
			std::vector<const char *> extensionNames(extensionCount);
			SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());
			createInfo.enabledExtensionCount = extensionNames.size();
			createInfo.ppEnabledExtensionNames = extensionNames.data();
			//End of Copy
			createInfo.enabledLayerCount = 0;

			if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
				run = true;
			} else {
				std::cout << "ERROR: Mya::initGraphics(): failed to create vk instance!\n";
			}
		}
	}
	return false;
}

void Mya::render(){}

void Mya::update(){
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){
			run = false;
		}
	}
}

void Mya::onExit(){
	std::cout << "Mya shutting down!\n";
	vkDestroyInstance(instance, nullptr);
	SDL_DestroyWindow(window);
}

bool Mya::getRunning(){
	return run;
}

void Mya::setWindowName(std::string _window_name){
	WINDOW_NAME = _window_name;
}

void Mya::setAppVersion(short x, short y, short z){
	APP_VERSION_PRIMARY = x;
	APP_VERSION_SECONDARY = y;
	APP_VERSION_TERTIARY = z;
}

const char Mya::getOS(){
	return *SDL_GetPlatform();
}