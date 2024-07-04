#pragma once
#include "header.h"

#include "Singleton.h"

/**
 * 引擎类，用于生成窗口。
 * 
 * 使用方法：
 * 1. initialize()：初始化，例如SDL相关内容
 * 2. mainLoop(int, char**)：主循环
 * 
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

	/* 
	 * 该方法用于初始化，例如SDL相关内容。
	 * 初始化失败会弹窗并终止程序。
	 */
	void initialize();

	/*
	 * 主循环。
	 */
	void mainLoop(int arg, char** args);

public:
	// ---------- 其他方法 ----------
	/*
	 * 该方法用于子类的额外初始化。
	 * 例如初始化窗口大小。
	 * 
	 * @return 返回 0 表示初始化成功，返回 1 表示初始化失败。
	 */
	virtual int virtInitialize() { return 0; };
	
	/*
	 * 该方法用于子类的额外初始化。
	 *
	 * @return 返回 0 表示初始化成功，返回 1 表示初始化失败。
	 */
	
private:
	// ---------- 私有成员 ----------
	SDL_Window* m_pWindow = nullptr;			// 主窗口
	SDL_Renderer* m_pRenderer = nullptr;		// 渲染器

	std::string m_strTitile = "BaseEngine";		// 窗口标题

private:
	// ---------- 私有方法 ----------
	void initAssert(bool bFlag, const char* strMsg) {
		if (bFlag) return;

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", strMsg, m_pWindow);
		exit(-1);
	}
};

