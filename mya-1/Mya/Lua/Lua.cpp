#include "Lua.h"

#include "../Mya.h"
#include "../Assets.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"
#include "../Graphics/TextView.h"
#include "../Sound/Sound.h"
#include "../Sound/Music.h"
#include "../Graphics/Animation.h"
//#include "../Utils/FileHandler.h"

Lua::Lua() {
	lua.open_libraries();
}

void Lua::exec(std::string command) {
	lua.script(command);
}

void Lua::loadMya(Mya* mya) {
	lua.set_function("mya_getMya", &Mya::getMya, mya);
	lua.set_function("mya_close", &Mya::close, mya);
	lua.set_function("mya_exit", &Mya::exit, mya);
	lua.set_function("mya_getAssets", &Mya::getAssets, mya);
	lua.set_function("mya_getFPS", &Mya::getFps, mya);
	lua.set_function("mya_getFullscreen", &Mya::getFullscreen, mya);
	lua.set_function("mya_getIsServer", &Mya::getIsServer, mya);
	lua.set_function("mya_getRenderer", &Mya::lua_getRenderer, mya); //Uses special function to work with lua (returns address of SDL_Renderer for other special lua functions to cast to)
	lua.set_function("mya_getVersion", &Mya::getVersion, mya);
	lua.set_function("mya_init", &Mya::init, mya);
	lua.set_function("mya_isRunning", &Mya::isRunning, mya);
	lua.set_function("mya_render", &Mya::render, mya);
	lua.set_function("mya_setFullscreen", &Mya::setFullscreen, mya);
	lua.set_function("mya_update", &Mya::update, mya);
	lua.set_function("mya_setWindowTitle", &Mya::setWindowTitle, mya);
	lua.set_function("mya_setWindowIcon", &Mya::setWindowIcon, mya);
	lua.set_function("mya_showCursor", &Mya::showCursor, mya);
	lua.set_function("mya_getWidth", &Mya::getWidth, mya);
	lua.set_function("mya_getHeight", &Mya::getHeight, mya);
	lua.set_function("mya_getPath", &Mya::getPath, mya);
	lua.set_function("mya_setRenderDrawColor", &Mya::setRenderDrawColor, mya);
	lua.set_function("mya_setUPS", &Mya::setUPS, mya);
	lua.set_function("mya_getUPS", &Mya::getUPS, mya);
	lua.set_function("mya_deltaUpdate", &Mya::deltaUpdate, mya);
	lua.set_function("mya_getDelta", &Mya::getDelta, mya);
	lua.set_function("mya_setIsOnTop", &Mya::setIsOnTop, mya);
}

void Lua::loadGraphics() {
	lua.new_usertype<Texture>("Texture",
		sol::constructors<Texture(), Texture(std::string, Mya*)>(),
		"destroy", &Texture::destroy,
		"getW", &Texture::getW,
		"getH", &Texture::getH);

	lua.new_usertype<Font>("Font",
		sol::constructors<Font(std::string, int)>(),
		"destroy", &Font::destroy);

	lua.new_usertype<Assets>("Assets",
		sol::constructors<Assets(Mya*)>(),
		"loadTexture", &Assets::loadTexture,
		"getTexture", &Assets::getTexture,
		"getTotalAssets", &Assets::getTotalAssets);

	lua.new_usertype<Sprite>("Sprite",
		sol::constructors<Sprite(Texture*)>(),
		"destroy", &Sprite::destroy,
		"update", &Sprite::update,
		"render", &Sprite::lua_render,
		"renderFlip", &Sprite::lua_renderFlip,
		"renderDefault", &Sprite::lua_renderDefault,
		"setX", &Sprite::setX,
		"setY", &Sprite::setY,
		"getX", &Sprite::getX,
		"getY", &Sprite::getY,
		"isColliding", &Sprite::isColliding,
		"isPointColliding", &Sprite::isPointColliding,
		"setRenderOutline", &Sprite::setRenderOutline,
		"setOutlineColor", &Sprite::setOutlineColor,
		"setTexture", &Sprite::setTexture);

	lua.new_usertype<TextView>("TextView",
		sol::constructors<TextView(Font, std::string, int, int, void*)>(),
		"render", &TextView::lua_render,
		"renderWH", &TextView::lua_renderWH,
		"setXY", &TextView::setXY,
		"setText", &TextView::lua_setText,
		"getText", &TextView::getText,
		"setColor", &TextView::setColorInt,
		"setFont", &TextView::lua_setFont,
		"getWidth", &TextView::getWidth,
		"getHeight", &TextView::getHeight);

	lua.new_usertype<Animation>("Animation",
		sol::constructors<Animation(std::string, int, int, Assets*)>(),
		"render", &Animation::lua_render,
		"renderFlip", &Animation::lua_renderFlip,
		"renderDefault", &Animation::lua_renderDefault,
		"setFrame", &Animation::setFrame,
		"setTexID", &Animation::setTexID,
		"setFPS", &Animation::setFPS,
		"setX", &Animation::setX,
		"setY", &Animation::setY,
		"isColliding", &Animation::isColliding,
		"isPointColliding", &Animation::isPointColliding,
		"setLooped", &Animation::setLooped,
		"isFinished", &Animation::isFinished,
		"reset", &Animation::reset);

	/*lua.new_usertype<FileHandler>("FileHandler",
		sol::constructors<FileHandler()>(),
		"listDir", &FileHandler::listDir,
		"getSize", &FileHandler::getSize,
		"get", &FileHandler::get,
		"dirExists", &FileHandler::dirExists,
		"fileExists", &FileHandler::fileExists,
		"createDir", &FileHandler::createDir,
		"createFile", &FileHandler::createFile);*/
}

void Lua::loadAudio() {
	lua.new_usertype<Sound>("Sound",
		sol::constructors<Sound(std::string)>(),
		"destroy", &Sound::destroy,
		"play", &Sound::play,
		"setVolume", &Sound::setVolume,
		"getVolume", &Sound::getVolume);

	lua.new_usertype<Music>("Music",
		sol::constructors<Music(std::string)>(),
		"destroy", &Music::destroy,
		"play", &Music::play,
		"pause", &Music::pause,
		"resume", &Music::resume,
		"isPaused", &Music::isPaused,
		"stop", &Music::stop,
		"isPlaying", &Music::isPlaying,
		"setVolume", &Music::setVolume,
		"getVolume", &Music::getVolume);
}