#include <iostream>

#include "Mya\Mya.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	Mya mya;

	bool run = mya.init("Partisan", 1280, 720);
	
	if (run) {
		while (mya.isRunning()) {
			mya.update();
			mya.render();
		}
		mya.close();
	}

	return 1;
}