#pragma once

#include "Tile.h"
#include "Point.h"
#include "MyString.h"

/**
 * 瓦片管理器。用于储存所有瓦片和从地图数据文件中加载瓦片数据。
 */
class TileManager
{
public:
	TileManager() = default;
	TileManager(Point position) : m_oPosition(position)	{}

	virtual ~TileManager() = default;


public:
	/**
	 * 从路径中加地图数据文件作为瓦片数据。
	 */
	bool load(const std::string& path);

public:
	/**
	 * 获取瓦片地图的宽度。
	 */
	size_t getWidth() const {
		if (m_vecTiles.empty()) return 0;
		else return m_vecTiles[0].size();
	}

	/**
	 * 获取瓦片地图的高度。
	 */
	size_t getHeight() const {
		return m_vecTiles.size();
	}

	/**
	 * 根据瓦片坐标获取指定位置的瓦片。
	 */
	const Tile& getTile(int x, int y) const { return m_vecTiles[y][x]; }

	/**
	 * 根据瓦片坐标获取指定位置的瓦片。
	 */
	const Tile& getTile(const Point& point) const { return m_vecTiles[point.y][point.x]; }

	/**
	 * 根据虚坐标获取指定位置的瓦片。
	 */
	const Tile& getTileByVirtualPosition(int x, int y) const {
		const int SIZE = Tile::TILE_SIZE;
		int tileX = (x - m_oPosition.x) / SIZE;
		int tileY = (y - m_oPosition.y) / SIZE;
		if (tileX < 0 || tileX >= getWidth() || tileY < 0 || tileY >= getHeight()) {
			std::cout << "Invalid tile position: (" << tileX << ", " << tileY << ")" << std::endl;
			return Tile::INVALID_TILE;
		}

		return m_vecTiles[tileY][tileX];
	}

	/**
	 * 根据虚坐标获取指定位置的瓦片。
	 */
	const Tile& getTileByVirtualPosition(const Point& point) const { 
		return getTileByVirtualPosition(point.x, point.y);
	}

	/**
	 * 设置瓦片地图位置。
	 */
	void setPosition(const Point& position) { m_oPosition = position; }

	/** 
	 * 获取瓦片地图位置。
	 */
	const Point& getPosition() const { return m_oPosition; }

private:
	Point m_oPosition;		// 整个瓦片地图的位置
	TileMap m_vecTiles;		// 瓦片地图

private:
	/* 解析string为Tile。*/
	void ParseTile(Tile& tile, const MyString& data);

};

