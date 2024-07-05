#pragma once

/**
 * 这是一个接口类。
 * 该类是观察者设计模式中的观察者。
 * 提供一个被通知的接口。
 */
class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;

public:
	/* 是否可以被通知，如果可以被通知则返回true */
	virtual bool canBeNotified() = 0;

	/* 被通知 */
	virtual void beNotified(int value) = 0;
};