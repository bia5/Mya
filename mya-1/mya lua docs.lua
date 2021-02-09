--Functions and Callbacks For Mya 1.5.0 (Codename: Gahyeon)

--Functions
mya_getMya() --Returns current mya (Needed for other functions)
mya_close() --Cleans up mya so its safe for program exit (should always be the last thing ran)
mya_exit() --Sets mya_isRunning() to false
mya_getFPS() --Returns a int for the current amount of fps
mya_getFullscreen() --Returns a bool whether mya's window is in fullscreen mode
mya_getIsServer() --Returns whether mya is in server mode
mya_getRenderer() --Returns current renderer (Needed for other functions)
mya_getVersion() --Returns a string of mya version
mya_init("Window Title", 1280, 720) --Initilizes mya and creates a window (Arg1 is a string of the title, Arg2 is window width, Arg3 is window height)
mya_isRunning() --Returns a bool whether mya should continue functioning.
mya_render() --Renders a frame (Will callback to event_render())
mya_setFullscreen(true) --Will set mya's window to fullscreen, true if fullscreen, false if windowed.
mya_update() --Runs a update loop (Will callback to event_update())
mya_setWindowTitle("Window Title") --Sets mya's window's title.
mya_setWindowIcon("assets\\icon.png") --Will try to set mya's window's icon to the image's path according to "Mya-Yasmine.exe"
mya_showCursor(true) --Sets if the os's cursor will show when hovering over mya's window
mya_getWidth() --Returns an int with mya's window's current width.
mya_getHeight() --Returns an int with mya's window's current height.


--Graphics
shader = Shader.new("/assets/shaders/vertexshader.vert","/assets/shaders/fragmentshader.frag")
shader:use()
shader:setBool("var", true)
shader:setInt("var", 69)
shader:setFloat("var", 6.9)
shader:destroy()

texture = Texture.new("/assets/texture/error.png")
texture:use()
texture:destroy()

sprite = Sprite.new(0, 0, 1, 1, shader, texture)
sprite:render()
sprite:destroy()
sprite:setX(1)
sprite:setY(1)
sprite:setW(1)
sprite:setH(1)
sprite:getX()
sprite:getY()
sprite:getW()
sprite:getH()
sprite:isColliding(sprite2)
sprite:isPointColliding(0.5, 0.5)
sprite:isPointInRect(0.5, 0.5, 0, 0, 1, 1)


--Network
network = Network.new()
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


--Audio
sound = Sound.new("assets/sound.wav") --arg1: asset location
sound:destroy()
sound:play()
sound:setVolume(64) --arg1: volume (0-128)
sound:getVolume() --returns int, which is the volume

music = Music.new("assets/music.wav") --arg1: asset location
music:destroy()
music:play()
music:pause()
music:resume()
music:stop()
music:isPlaying() --returns bool, whether music is playing
music:setVolume(64) --arg1: volume (0-128)
music:getVolume() --returns int, which is the volume


--Callbacks
function event_mouseMotion(x, y) end -- x and y equals the user's mouse's new coords apparent to window.
function event_mouseButtonDown(btn) end --Is called when a mouse button is pressed down. btn equals a string which defines which mouse button was pressed. (mess around using print(btn) to find what each button is defined as)
function event_mouseButtonUp(btn) end --Called when a mouse button is released.
function event_keyDown(key) end --called when a keyboard key is pressed down.
function event_keyUp(key) end --Called when a keyboard key is released.
function event_networkMessage(clientMessage) end --Called when the program recieves a network message.
function event_update() end --called on every update loop.
function event_windowResize(w, h) end --called when window is resized
function event_render() end --called on render loop.
function event_tupdate() end --called for every tick update
