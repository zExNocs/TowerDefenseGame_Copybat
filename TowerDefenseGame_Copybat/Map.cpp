#include "Map.h"

/*  */
void Map::load(const std::string& path) {
	m_oTileManager.load(path);		// 加载路径

}

/* 生成地图的缓存：怪物生成点、基地 */
void Map::GenerateMapCache() {
	for (int iY = 0; iY < m_oTileManager.getHeight(); iY++) {
		for (int iX = 0; iX < m_oTileManager.getWidth(); iX++) {
			const Tile& tile = m_oTileManager.getTile(iX, iY);
			if (tile.getSpecialFlag() == 0) m_oBase = Point(iX, iY);
		}
	}
}