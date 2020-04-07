#include "Lua.h"

#include "../Mya.h"
#include "../Graphics/Assets.h"
#include "../Graphics/Texture.h"
#include "../Network/Network.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"
#include "../Graphics/TextView.h"
#include "../Utils/FileSystemHelper.h"
#include "../Sound/Sound.h"
#include "../Sound/Music.h"

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
	//lua.set_function("mya_getWindow", &Mya::getWindow, mya);
	lua.set_function("mya_init", &Mya::init, mya);
	//lua.set_function("mya_initLua", &Mya::initLua, mya); //not needed
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
}

void Lua::loadMya_t() { //This is kinda useless... This needs a revison!
	lua.new_usertype<Mya>("Mya",
		"init", &Mya::init,
		"update", &Mya::update,
		"render", &Mya::render,
		"exit", &Mya::exit,
		"isRunning", &Mya::isRunning,
		"close", &Mya::close,
		"setFullscreen", &Mya::setFullscreen,
		"getFullscreen", &Mya::getFullscreen);
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
		"getFont", &Assets::getFont,
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

	lua.new_usertype<FileSystemHelper>("FileSystemHelper",
		sol::constructors<FileSystemHelper()>(),
		"getAllFoldersInADirectory", &FileSystemHelper::getAllFoldersInADirectory,
		"getAllFilesInADirectory", &FileSystemHelper::getAllFilesInADirectory);
}

void Lua::loadNetwork() {
	lua.new_usertype<Network>("Network",
		sol::constructors<Network()>(),
		"init", &Network::init,
		"update", &Network::lua_update,
		"sendMessage", &Network::sendMessage,
		"broadcast", &Network::broadcast,
		"allocPacket", &Network::allocPacket,
		"refreshIP", &Network::refreshIP,
		"refreshPing", &Network::refreshPing,
		"isIPRegistered", &Network::isIPRegistered,
		"getIPLoc", &Network::getIPLoc,
		"kickIP", &Network::kickIP,
		"getIP", &Network::getIP,
		"getPing", &Network::getPing,
		"setServerName", &Network::setServerName,
		"getServerName", &Network::getServerName,
		"setServerPort", &Network::setServerPort,
		"getServerPort", &Network::getServerPort,
		"setIsServer", &Network::setIsServer,
		"getIsServer", &Network::getIsServer,
		"getPacketSize", &Network::getPacketSize,
		"setPacketAmt", &Network::setPacketAmt,
		"getPacketAmt", &Network::getPacketAmt,
		"setDebugMode", &Network::setDebugMode,
		"getDebugMode", &Network::getDebugMode,
		"setMaxClients", &Network::setMaxClients,
		"getMaxClients", &Network::getMaxClients,
		"getClientCount", &Network::getClientCount,
		"getTotalPacketsSent", &Network::getTotalPacketsSent,
		"getTotalPacketsRecv", &Network::getTotalPacketsRecv,
		"getTotalBitsSent", &Network::getTotalBitsSent,
		"getTotalBitsRecv", &Network::getTotalBitsRecv,
		"getTimedPacketsSent", &Network::getTimedPacketsSent,
		"getTimedPacketsRecv", &Network::getTimedPacketsRecv,
		"getTimedBitsSent", &Network::getTimedBitsSent,
		"getTimedBitsRecv", &Network::getTimedBitsRecv,
		"getDataFromClientMessage", &Network::getDataFromClientMessage,
		"getIPFromClientMessage", &Network::getIPFromClientMessage,
		"setPort", &Network::setPort,
		"getPort", &Network::getPort,
		"close", &Network::close);
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