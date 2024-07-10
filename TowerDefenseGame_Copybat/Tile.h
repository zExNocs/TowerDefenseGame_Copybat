#pragma once

#include <vector>
#include "Renderable.h"

/**
 * 瓦片类游戏的瓦片数据。
 * 
 * 该类用于控制各种瓦片的数据以及根据数据进行渲染绘制。
 */
class Tile :
	public Renderable
{
public:
	/* 敌人运动方向的数据类型 */
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

public:
	static const int DEFAULT_TERRIAN = -1;
	static const int DEFAULT_DECORATION = -1;
	static const Direction DEFAULT_DIRECTION = Direction::None;
	static const int DEFAULT_SPECIAL_FLAG = -1;
	static const int TILE_SIZE = 48;		/* 瓦片的长宽像素数 */

	static const Tile INVALID_TILE;		/* 无效瓦片 */

public:
	Tile() = default;
	virtual ~Tile() = default;

public:
	/* 瓦片的渲染 */
	void onRender() override;

public:
	/* 此处是否有防御塔：getter 和 setter  */
	bool hasTower() const { return m_bHasTower; }
	void setHasTower(bool bHasTower) { m_bHasTower = bHasTower; }

	/* 地貌图片索引：getter 和 setter */
	int getTerrian() const { return m_iTerrian; }
	void setTerrian(int iTerrian) { m_iTerrian = iTerrian; }

	/* 装饰图片索引：getter 和 setter */
	int getDecoration() const { return m_iDecoration; }
	void setDecoration(int iDecoration) { m_iDecoration = iDecoration; }

	/* 特殊数据/图片索引：getter 和 setter */
	int getSpecialFlag() const { return m_iSpecialFlag; }
	void setSpecialFlag(int iSpecialFlag) { m_iSpecialFlag = iSpecialFlag; }

	/* 移动方向 getter 和 setter */
	Direction getDirection() const { return m_eDirection; }
	void setDirection(Direction eDirection) { m_eDirection = eDirection; }
	void setDirection(int iDirection) { if (iDirection >= 0 && iDirection <= 4) m_eDirection = static_cast<Direction>(iDirection); else m_eDirection = Direction::None; }

private:
	int m_iTerrian = 0;			// 地貌图片索引
	int m_iDecoration = -1;		// 装饰图片索引
	int m_iSpecialFlag = -1;	// 特殊数据/图片索引
	Direction m_eDirection = Direction::None;	// 移动方向

	bool m_bHasTower = false;	// 此处是否有防御塔
};

typedef std::vector< std::vector<Tile> > TileMap;