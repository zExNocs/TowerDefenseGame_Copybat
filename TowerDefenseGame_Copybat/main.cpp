#define SDL_MAIN_HANDLED
#include "header.h"
#include "BaseEngine.h"
#include "MyStringTest.h"	

int main(int argc, char** argv) {

	/*
	BaseEngine::getInstance()->initialize();
	BaseEngine::getInstance()->mainLoop(argc, argv);
	BaseEngine::getInstance()->deinitialize();
	*/

	MyStringTest qwq;
	qwq.run();

	return 0;
}