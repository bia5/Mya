#include "Mya\Mya.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
	Mya mya;
	mya.init("Partisan", 1280, 720);
	while (mya.isRunning()) {
		mya.update();
		mya.render();
		mya.lua->exec("print('hai from lua')");
#ifdef __EMSCRIPTEN__
		emscripten_sleep(0);
#endif
	}
	//mya.close();

	return 0;
}