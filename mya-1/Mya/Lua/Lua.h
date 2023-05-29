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
	void loadGraphics();
	void loadNetwork();
	void loadAudio();
};