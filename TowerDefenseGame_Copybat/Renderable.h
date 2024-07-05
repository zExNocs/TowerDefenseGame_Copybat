#pragma once

#include "Observer.h"

/**
 * 这是一个接口类。
 * 该类提供一个绘制的接口。
 */
class Renderable :
	public Observer
{
public:
	Renderable() = default;
	virtual ~Renderable() = default;

public:
	/* 绘制 */
	virtual void onRender() = 0;

	/* 通知: 绘制 */
	virtual void beNotified(int value) override { onRender(); }

	/* 默认可以被通知 */
	virtual bool canBeNotified() override { return true; }
};

