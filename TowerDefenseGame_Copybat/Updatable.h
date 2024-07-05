#pragma once

#include "Observer.h"

/**
 * 这是一个接口类。
 * 该类提供一个更新的接口。
 */
class Updatable :
	public Observer
{
public:
	Updatable() = default;
	virtual ~Updatable() = default;

public:
	/* 更新 */
	virtual void onUpdate(int delta) = 0;

	/* 通知: 更新 */
	virtual void beNotified(int value) override { onUpdate(value); }

	/* 默认可以被通知 */
	virtual bool canBeNotified() override { return true; }
};