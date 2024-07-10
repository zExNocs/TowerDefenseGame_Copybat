#pragma once

#include "Point.h"
#include "TileManager.h"

/**
 * 用于直接储存地图关卡数据。
 */
class Map
{
public:
	Map() = default;
	~Map() = default;

public:
	/**
	 * 根据路径加载地图并生成地图缓存。
	 */
	void load(const std::string& path);
	

private:
	TileManager m_oTileManager;
	Point m_oBase;

private:
	/* 根据tileManager来生成地图的缓存。*/
	void GenerateMapCache();
};

