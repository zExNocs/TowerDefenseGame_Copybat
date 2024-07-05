#pragma once

#include "Singleton.h"

class DataManager :
	public Singleton<DataManager> 
{
	friend class Singleton<DataManager>;

public:
	// ---------- 窗口相关 ---------- 
	int WINDOW_WIDTH = 1280;	// 窗口宽度
	int WINDOW_HEIGHT = 720;	// 窗口高度
	int FPS = 60;				// 帧数
};