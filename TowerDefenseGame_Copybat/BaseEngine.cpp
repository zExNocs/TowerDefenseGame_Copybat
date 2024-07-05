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
	int iWindowWidth = DataManager::getInstance()->WINDOW_WIDTH;
	int iWindowHeight = DataManager::getInstance()->WINDOW_HEIGHT;
	m_pWindow = SDL_CreateWindow(m_strTitile.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, iWindowWidth, iWindowHeight, SDL_WINDOW_SHOWN);
	initAssert(m_pWindow, u8"创建游戏窗口失败！");

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	initAssert(m_pRenderer, u8"创建渲染器失败！");
}

/* 去初始化 */
void BaseEngine::deinitialize() {
	// 摧毁SDL相关对象
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	// 退出SDL内容
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	// 去初始化其他内容
	virtDeinitialize();
}

/* 主循环 */
int BaseEngine::mainLoop(int argc, char** argv) {
	SDL_Event oEvent;

	while (!m_iQuitCode) {
		// 输入处理
		while (SDL_PollEvent(&oEvent)) onInput(oEvent);

		// 更新时间
		int delta = updateTick();	

		// 数据更新
		onUpdate(delta);

		// 图像渲染
		onRender();
	}

	return 0;
}



// ---------- 输入处理相关 ----------
// 输入处理
void BaseEngine::onInput(SDL_Event& oEvent) {

}



// ---------- 渲染相关 ----------
// 图像渲染
void BaseEngine::onRender() {
	if (!m_bNeedRender) return;


	SDL_RenderPresent(m_pRenderer);
	m_bNeedRender = false;
}



// ---------- 数据更新相关 ----------
/**
 * 该方法用于所有处理数据更新。
 */
void BaseEngine::onUpdate(int delta) {
	// 更新对象前的数据更新 
	virtBeforeUpdate(delta);

	// 更新所有可更新对象容器的对象
	m_oUpdatableManager.notifyAll(delta);

	// 更新对象后的数据更新
	virtAfterUpdate(delta);
}



// ---------- 计时相关 ----------
// tick更新并返回与上次更新的时间差值。
int BaseEngine::updateTick() {
	int FPS = DataManager::getInstance()->FPS;

	long long lastTick = m_iTick;
	m_iTick = SDL_GetTicks();

	double delta = m_iTick - lastTick;
	// 没有到达预期时间
	if (delta < 1000.0 / FPS) {
		SDL_Delay((Uint32)(1000.0 / FPS - delta));	// 延迟
		m_iTick = SDL_GetTicks();	// 获取新的时间
	}
	return m_iTick - lastTick;
}