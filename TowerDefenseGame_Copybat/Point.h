#ifndef _POINT_H_
#define _POINT_H_


#include <cmath>
#include <iostream>

struct Point {
	// ----- 成员变量 -----
	int x;
	int y;

	// ----- 构造函数 ----- 
	Point (int x = 0, int y = 0) : x(x), y(y) {}

	Point (const Point& point) : x(point.x), y(point.y){}
	
	// ----- 运算符重载 ----- 
	// 点之间相加
	Point operator+ (const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	// 点之间相减
	Point operator- (const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	// 点之间相乘
	Point operator* (int scalar) const {
		return Point(x * scalar, y * scalar);
	}

	// 与标量相乘
	Point operator* (const Point& rhs) const {
		return Point(x * rhs.x, y * rhs.y);
	}

	// 点之间相除
	Point operator/ (const Point& rhs) const {
		return Point(x / rhs.x, y / rhs.y);
	}

	// 与标量相除
	Point operator/ (int scalar) const {
		if (scalar != 0) return Point(x / scalar, y / scalar);
		else throw std::invalid_argument("Division by zero");
	}

	// 等于赋值
	Point& operator= (const Point& rhs) {
		if (this != &rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
		}
		return *this;
	}

	// 判断相等
	bool operator== (const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	// 判断不相等
	bool operator!= (const Point& rhs) const {
		return !(*this == rhs);
	}

	// 重载输出运算符
	friend std::ostream& operator<< (std::ostream& os, const Point& point);

	// ----- 相关函数 -----
	// 打印函数
	void print() const {
		std::cout << "Point(" << x << ", " << y << ")" << std::endl;
	}

	// 模长 (到原点的距离)
	double magnitude() const {
		return ::sqrt(::pow(x, 2) + ::pow(y, 2));
	}

	// 两点之间的距离
	double distance(const Point& rhs) const {
		return ::sqrt(::pow(x - rhs.x, 2) + ::pow(y - rhs.y, 2));
	}

	// 点乘
	int dot(const Point& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	// 叉乘
	int cross(const Point& rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	// 两点之间的夹角 (弧度)
	double angleTo(const Point& rhs) const {
		double dotProd = this->dot(rhs);
		double mag1 = this->magnitude();
		double mag2 = rhs.magnitude();
		return std::acos(dotProd / (mag1 * mag2));
	}

	// 与水平线的夹角 (弧度)
	double angleWithHorizontal() const {
		return std::atan2(y, x);
	}
};

// 输出运算符重载的实现
std::ostream& operator<< (std::ostream& os, const Point& point) {
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

// 友元函数，支持标量在左侧的乘法运算符重载
Point operator* (int scalar, const Point& point) {
	return Point(point.x * scalar, point.y * scalar);
}


#endif // !_POINT_H_