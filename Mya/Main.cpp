#include <iostream>
#include <string>

#include "Mya/Mya.h"
#include "Wrappers/LuaWrap.h"

int main(int argc, char* argv[]){
    std::cout << "Testing c++ main: Hello World!\n";
    LuaWrap luaW;
    
    Mya mya;
    mya.setWindowName("Mya Test Build");
    mya.initGraphics();
    while(mya.getRunning()){
        mya.update();
        mya.render();
    }
    mya.onExit();

    std::cout << "Exiting main c++!\n";
    return 0;
}