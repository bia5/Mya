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
#ifdef __EMSCRIPTEN__
		emscripten_sleep(0);
#endif
	}
	//mya.close();

	return 0;
}