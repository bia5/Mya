g++ -std=c++17 ./Mya/Main.cpp ./Mya/Mya/* ./Mya/Wrappers/* -I./lib/include -I./windows_lib/include -L./windows_lib/lib -L./lib/lib -w -lmingw32 -lSDL2main -lSDL2 -llua -o ./build_windows/Mya