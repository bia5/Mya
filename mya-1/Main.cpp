#include <iostream>
#include <Windows.h>

#include "Mya\Mya.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	static Mya mya;
	mya.initLua();

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if ((arg == "-s") || (arg == "-server")) {
			std::cout << "Setting it to server mode!" << std::endl;
			mya.isServer = true;
		}
		if ((arg == "-c") || (arg == "-console")) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
		}
	}

	sol::load_result lr = mya.lua->lua.load_file("lua/main.lua");
	if (!lr.valid()) {
		sol::error err = lr;
		std::string what = err.what();
		std::cout << "call failed, sol::error::what() is " << what << std::endl;
		system("pause");
	} else {
		sol::protected_function_result result1 = lr();
		if (!result1.valid()) {
			sol::error err = result1;
			std::string what = err.what();
			std::cout << "call failed, sol::error::what() is " << what << std::endl;
			system("pause");
		} else
			std::cout << "OK" << std::endl;
	}

	return 1;
}