#pragma once
#include "header.h"

#include "Singleton.h"
#include "ObserverContainer.h"

/**
 * 引擎类，用于生成窗口。
 * 
 * 使用方法：
 * 1. initialize()：初始化，例如SDL相关内容
 * 2. mainLoop(int, char**)：主循环
 * 3. deinitialize()：去初始化，释放相关内存空间。
 */
class BaseEngine :
	public Singleton<BaseEngine>
{
	friend class Singleton<BaseEngine>;

public:
	BaseEngine() = default;
	virtual ~BaseEngine() = default;


public:
	// ---------- 使用方法相关 ----------
	/** 
	 * 该方法用于初始化，例如SDL相关内容。
	 * 初始化失败会弹窗并终止程序。
	 */
	void initialize();

	/**
	 * 主循环。
	 */
	int mainLoop(int argc, char** argv);

	/**
	 * 该方法用于去初始化，例如退出SDL相关内容。
	 */
	void deinitialize();

public:
	// ---------- 输入处理相关 ----------
	/**
	 * 该方法用于处理制定的相关输入事件。
	 */
	void onInput(SDL_Event& oEvent);



public:
	// ---------- 数据更新相关 ----------
	/**
	 * 该方法用于所有处理数据更新。
	 * 顺序如下：
	 * 1. 更新对象前的数据更新 (例如更新倒计时、分数)
	 * 2. 更新所有可更新对象容器的对象
	 * 3. 更新对象后的数据更新 (例如碰撞检测、删除死亡对象)
	 */
	void onUpdate(int delta);

	/**
	 * 获取更新对象容器
	 */
	ObserverContainer* getUpdatableManager() { return &m_oUpdatableManager; }

	/**
	 * 虚函数：更新对象前的数据更新。
	 */
	virtual void virtBeforeUpdate(int delta) {}

	/**
	 * 虚函数：更新对象后的数据更新。
	 */
	virtual void virtAfterUpdate(int delta) {}



public:
	// ---------- 渲染相关 ----------
	/**
	 * 该方法用于所有处理图像渲染。
	 */
	void onRender();

	/**
	 * 该方法用于设置当前更新需要进行渲染。
	 */
	void needToRender() { m_bNeedRender = true; }

	/**
	 * 获取渲染容器
	 */
	ObserverContainer* getRenderableManager() { return &m_oRenderableManager; }



public:
	// ---------- 计时相关 ----------
	/**
	 * 该方法用于时间tick更新，并返回与上次更新的时间差值。
	 * 如果没有到达预期更新的时间，则会休眠到预期的时间。
	 * 
	 */
	int updateTick();

	/**
	 * 该方法用于暂停并记录暂停的时间。
	 */
	void pause() { 
		if (m_iPausedTick == -1) m_iPausedTick = m_iTick; 
		needToRender();
	}

	/**
	 * 该方法用于解除暂停，并计算暂停时间。
	 */
	void unpause() {
		m_iTickOffset += m_iTick - m_iPausedTick;	// 计算暂停时长
		m_iPausedTick = -1;							// 解除暂停
		needToRender();
	}

	/**
	 * 该方法用于判断是否处于暂停时间。
	 */
	bool isPaused() const { return m_iPausedTick != -1; }

	/**
	 * 该方法用于返回除去暂停时间的当前 tick (ms)
	 */
	long long getModifiedTick() const {
		if (m_iPausedTick != -1) return m_iPausedTick - m_iTickOffset;	// 当前暂停中
		else return m_iTick - m_iTickOffset;	// 当前没有暂停
	}

	/**
	 * 该方法用于返回当前 raw tick (ms)
	 */
	long long getRawTick() const { return m_iTick; }



public:
	// ---------- 其他虚拟方法 ----------
	/*
	 * 该方法用于子类的额外初始化。
	 * 例如初始化窗口大小。
	 * 
	 * @return 返回 0 表示初始化成功，返回 1 表示初始化失败。
	 */
	virtual int virtInitialize() { return 0; }
	
	/*
	 * 该方法用于子类的额外去初始化。
	 */
	virtual void virtDeinitialize() {}

public:
	// ---------- 其他方法 ----------
	/*
	 * 设置退出代码。
	 *
	 * @param iCode 设置的代码值。0 是不退出，其他值为退出。
	 */
	void setQuitCode(int iCode) {
		m_iQuitCode = iCode;
	}
	


private:
	// ---------- 私有成员 ----------
	SDL_Window* m_pWindow = nullptr;		// 主窗口
	SDL_Renderer* m_pRenderer = nullptr;	// 渲染器

	ObserverContainer m_oUpdatableManager;	// 可更新的对象容器
	ObserverContainer m_oRenderableManager; // 可渲染的对象容器

	// ----- 主循环相关 -----
	int m_iQuitCode = 0;		// 退出代码

	// ----- 计时器相关 -----
	long long m_iTick = 0;			// 当前更新的时间 (ms)
	long long m_iTickOffset = 0;	// 暂停的总时长 (ms)
	long long m_iPausedTick = -1;	// 暂停的时间点，如果为 -1 表示当前没有暂停

	// ----- 渲染相关 -----
	bool m_bNeedRender = false;		// 是否需要渲染



protected:
	// ---------- 保护成员 ----------
	std::string m_strTitile = "BaseEngine";		// 窗口标题



private:
	// ---------- 私有方法 ----------

	/* 初始化断言判断。如果为false则报错并退出程序。 */
	void initAssert(bool bFlag, const char* strMsg) {
		if (bFlag) return;

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", strMsg, m_pWindow);
		exit(-1);
	}
};