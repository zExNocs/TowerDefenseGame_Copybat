#pragma once

#include "Singleton.h"

class DataManager :
	public Singleton<DataManager> 
{
	friend class Singleton<DataManager>;

public:
	// ---------- ´°¿ÚÏà¹Ø ---------- 
	int WINDOW_WIDTH = 1280;
	int WINDOW_HEIGHT = 720;

};