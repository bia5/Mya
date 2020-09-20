#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

class LuaWrap{
public:
    //There shouldn't be a need for this to be public, but just incase you need to do any janky things it'll be public.
    sol::state lua;

    LuaWrap();

    void initMya();
private:
    //Ideally the sol::state would be private but idk
};