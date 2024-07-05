#pragma once

#include <memory>
#include <vector>

#include "Observer.h"

/**
 * 该类是观察者设计模式中的被观察者。
 * 是一个容器，可以添加和删除被观察者。
 */
class ObserverContainer {
public:
	ObserverContainer() = default;
	virtual ~ObserverContainer() = default;

public:
	/**
	 * 通知所有的观察者。
	 * 
	 * @param value 通知的值
	 */
	void notifyAll(int value) {
		// 删除所有智能指针已经到期的观察者。
		m_vecTempObservers.erase(
			std::remove_if(
				m_vecTempObservers.begin(), m_vecTempObservers.end(),
				[](const std::weak_ptr<Observer>& wp) { return wp.expired(); }
			),
			m_vecTempObservers.end()
		);

		// 通知剩下的所有观察者。
		for (auto& observer : m_vecTempObservers) {
			if (!observer.expired()) {
				std::shared_ptr<Observer> sp = observer.lock();
				if (sp->canBeNotified()) sp->beNotified(value);
			}
		}
	}

	/**
	 * 添加新的观察者。
	 * 
	 * @param pNewObserver 要添加的观察者
	 * @param isPerm 是否要永久储存
	 */
	void add(const std::shared_ptr< Observer >& pNewObserver, bool isPerm = false) {
		// 查找是否重复加入，it表示重复加入的对象迭代器
		auto it = std::find_if(
			m_vecTempObservers.begin(), m_vecTempObservers.end(),
			[&pNewObserver](const std::weak_ptr<Observer>& wp) { return !wp.owner_before(pNewObserver) && !pNewObserver.owner_before(wp); }
		);
		// 已经加入了，则不重复加，防止重复被通知。
		if (it != m_vecTempObservers.end()) return; 

		m_vecTempObservers.push_back(pNewObserver);
		if (isPerm) m_vecPermObservers.push_back(pNewObserver);
	}

	/**
	 * 删除指定的观察者。
	 *
	 * @param pObserver 要被删除的观察者。
	 */
	void remove(const std::shared_ptr< Observer >& pObserver) {
		m_vecTempObservers.erase(
			std::remove_if(m_vecTempObservers.begin(), m_vecTempObservers.end(),
				[&pObserver](const std::weak_ptr<Observer>& wp) { return !wp.owner_before(pObserver) && !pObserver.owner_before(wp); }
			),
			m_vecTempObservers.end()
		);

		m_vecPermObservers.erase(
			std::remove_if(m_vecPermObservers.begin(), m_vecPermObservers.end(),
				[&pObserver](const std::shared_ptr<Observer>& sp) { return !sp.owner_before(pObserver) && !pObserver.owner_before(sp); }
			),
			m_vecPermObservers.end()
		);
	}

	/**
	 * 删除所有的观察者。
	 */
	void clear() {
		m_vecTempObservers.clear();
		m_vecPermObservers.clear();
	}

private:
	std::vector< std::weak_ptr<Observer> > m_vecTempObservers;		// 临时储存的观察者。
	std::vector< std::shared_ptr<Observer> > m_vecPermObservers;	// 永久储存的观察者，一定被上者包含。
};