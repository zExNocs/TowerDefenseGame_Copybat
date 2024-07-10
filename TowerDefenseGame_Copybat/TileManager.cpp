#include "header.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "TileManager.h"

/* 从路径中加地图数据文件作为瓦片数据 */
bool TileManager::load(const std::string& path) {
	std::ifstream file(path);
	if (!file.good()) return false;

	TileMap tempTileMap;
	int iY = -1;

	std::string strLine;
	while (std::getline(file, strLine)) {
		MyString myStrLine = MyString(strLine).trim();
		if (myStrLine.empty()) continue;

		iY++;
		tempTileMap.emplace_back();

		std::vector<MyString> tokens = myStrLine.split(',');
		for (MyString& token : tokens) {
			tempTileMap[iY].emplace_back();
			Tile& tile = tempTileMap[iY].back();
			ParseTile(tile, token);
		}
	}
	file.close();

	// 校准
	if (tempTileMap.empty() || tempTileMap[0].empty()) return false;

	m_vecTiles = tempTileMap;

	return true;
}

/* 解析string为Tile */
void TileManager::ParseTile(Tile& tile, const MyString& data) {
	MyString tidyData = data.trim();
	
	std::vector<int> values;
	std::vector<MyString> tokens = tidyData.split('\\');

	for (MyString& token : tokens) {
		int value;
		try {
			value = std::stoi(token.to_string());
		} catch (const std::invalid_argument&) {
			value = -1;
		}
		values.push_back(value);
	}

	if (values.size() >= 1) tile.setTerrian(values[0]);
	else tile.setTerrian(Tile::DEFAULT_TERRIAN);
	if (values.size() >= 2) tile.setDecoration(values[1]);
	else tile.setDecoration(Tile::DEFAULT_DECORATION);
	if (values.size() >= 3) tile.setDirection(values[2]);
	else tile.setDirection(Tile::DEFAULT_DIRECTION);
	if (values.size() >= 4) tile.setSpecialFlag(values[3]);
	else tile.setSpecialFlag(Tile::DEFAULT_SPECIAL_FLAG);
}