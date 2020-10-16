#include "Mya.h"

Mya::Mya(){
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
			uint32_t extensionCount = 0;
			if(!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr)) 
				std::cout << "ERROR: Mya::initGraphics(): SDL_getExtensions (1)\n";
			std::vector<const char *> extensionNames(extensionCount);
			if(!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data())) 
				std::cout << "RROR: Mya::initGraphics(): SDL_getExtensions (2)\n";
			createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
			createInfo.ppEnabledExtensionNames = extensionNames.data();
			createInfo.enabledLayerCount = 0;
			if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
				std::cout << "ERROR: Mya::initGraphics(): failed to create vk instance!\n";
			extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			for (const auto& extension : extensions) { }
			uint32_t gpuCount = 0;
			vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr);
			if(gpuCount == 0)
				std::cout << "ERROR: Failed to find any GPUs with Vulkan support!\n";
			std::vector<VkPhysicalDevice> gpus(gpuCount);
			vkEnumeratePhysicalDevices(instance, &gpuCount, gpus.data());
			for (const auto& gpu : gpus) {
				if (isGPUCompat(gpu)) {
					physicalDevice = gpu;
					break;
				}
			}
			if (physicalDevice == VK_NULL_HANDLE)
				std::cout << "ERROR: Failed to find a suitable GPU!\n";

			run = true;
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

bool Mya::isGPUCompat(VkPhysicalDevice gpu){
	QueueFamilyIndices indices = findQueueFamilies(gpu);
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(gpu, &deviceProperties);
	vkGetPhysicalDeviceFeatures(gpu, &deviceFeatures);
	bool compat = true;

	if(!indices.isComplete())
		compat = false;

	return compat;
}

QueueFamilyIndices Mya::findQueueFamilies(VkPhysicalDevice device){
	QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for(const auto& queueFamily : queueFamilies) {
		if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;
		if(indices.isComplete())
			break;
		i++;
	}

	return indices;
}