#pragma once

#include <iostream>

class TestClass {
public:
	virtual int run() = 0;

public:
	void print(std::string str) {
		std::cout << str << std::endl;
	}

	/* 断言。如果正确返回 0，否则返回 1 */
	template <typename T>
	int assertEqual(T expected, T actual) {
		std::cout << "应该是 \"" << expected << "\", 实际是 \"" << actual <<"\", 这是";
		if (expected == actual) std::cout << "正确的";
		else {
			std::cout << "错误的！！！！！！！！！！！！！！！！！！！！！！！！";
		}
		std::cout << std::endl;

		return expected == actual ? 0 : 1;
	}
};