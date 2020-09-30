#include "LuaWrap.h"

//TODO Bind Lua

LuaWrap::LuaWrap(){
	lua.open_libraries();
	std::cout << "Testing Lua Wrapper: ";
	lua.script("print('Hello World from lua!')");
}

void LuaWrap::initMya(){
	
}