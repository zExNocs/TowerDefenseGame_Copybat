#ifndef _Singleton_H_
#define _Singleton_H_

#include <memory>

/**
 * 该类是单例设计模式(Singleton)的接口类。
 * 
 * 使用智能指针的方式来储存实例。
 * 使用模板的方式来储存不同类型的单例类。
 * 
 * 方法：
 * getInstance()：获取相应类的智能指针。
 * 
 */
template <typename T>
class Singleton
{
public:
	/* 析构函数 */
	virtual ~Singleton() = default;

public:
	/**
	 * 获取唯一实例。
	 * 如果没有创建过实例，则创建该实例。
	 * 
	 * @return 以继承类的形式返回单例模式的唯一实例
	 */
	static std::shared_ptr<T> getInstance() {
		if (!instance) instance = std::shared_ptr<T>(new T());

		return instance;
	}

protected:
	/* 构造函数 */
	Singleton() = default;

	/* 防止赋值 */
	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton&) = delete;

private:
	static std::shared_ptr<T> instance;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instance = nullptr;


#endif // !_Singleton_H_