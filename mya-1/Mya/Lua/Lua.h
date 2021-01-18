#pragma once

#include <iostream>

#include <sol/sol.hpp>

class Mya;

class Lua {
public:
	sol::state lua;

	Lua();

	void exec(std::string commad);

	void loadMya(Mya*);
	void loadMya_t();
	void loadGraphics();
	void loadNetwork();
	void loadAudio();
	void loadCol();
};