#include "BaseEngine.h"
#include "DataManager.h"

/* 游戏引擎的初始化 */
void BaseEngine::initialize() {
	// 初始化 SDL 相关内容
	initAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败！");
	initAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image 初始化失败！");
	initAssert(!TTF_Init(), u8"SDL_ttf 初始化失败！");
	initAssert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");
	initAssert(!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048), u8"SDL_mixer 媒体启动失败！");

	// 初始化其他内容
	initAssert(!virtInitialize(), u8"其他初始化失败！");


	// 启动IME
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");


	// 初始化窗口和渲染器
	int windowWidth = DataManager::getInstance()->WINDOW_WIDTH;
	int windowHeight = DataManager::getInstance()->WINDOW_HEIGHT;
	m_pWindow = SDL_CreateWindow(m_strTitile.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

}