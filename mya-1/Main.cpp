#include "Mya\Mya.h"

int main() {
	Mya mya;
	mya.initLua();
	sol::load_result lr = mya.lua->lua.load_file("lua/main.lua");
	if (!lr.valid()) {
		sol::error err = lr;
		std::string what = err.what();
		std::cout << "call failed, sol::error::what() is " << what << std::endl;
	}
	else {
		sol::protected_function_result result1 = lr();
		if (!result1.valid()) {
			sol::error err = result1;
			std::string what = err.what();
			std::cout << "call failed, sol::error::what() is " << what << std::endl;
		}
		else
			std::cout << "OK" << std::endl;
	}

	return 0;
}