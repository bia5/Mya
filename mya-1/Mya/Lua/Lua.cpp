#include "Lua.h"

#include "../Mya.h"
#include "../Network/Network.h"
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
	lua.set_function("mya_getFPS", &Mya::getFps, mya);
	lua.set_function("mya_getFullscreen", &Mya::getFullscreen, mya);
	lua.set_function("mya_getIsServer", &Mya::getIsServer, mya);
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
	lua.set_function("mya_setUPS", &Mya::setUPS, mya);
	lua.set_function("mya_getUPS", &Mya::getUPS, mya);
}

void Lua::loadGraphics() {
	
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
