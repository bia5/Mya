emcc -std=c++17 -O3 Main.cpp Mya/mya.cpp Mya/Utils/FPS.cpp Mya/Utils/Timer.cpp Mya/Utils/FileHandler.cpp Mya/Assets.cpp Mya/Graphics/TextView.cpp Mya/Graphics/Font.cpp Mya/Graphics/Texture.cpp Mya/Graphics/Sprite.cpp Mya/Graphics/Animation.cpp Mya/Sound/Music.cpp Mya/Sound/Sound.cpp Mya/Lua/Lua.cpp Mya/Network/Network.cpp --preload-file assets\ --preload-file lua\ --preload-file worlds\ -sASYNCIFY liblua54.a -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" -sUSE_SDL_TTF=2 -sUSE_SDL_MIXER=2 -sUSE_SDL_NET=2 -o MyaWeb.html
pause