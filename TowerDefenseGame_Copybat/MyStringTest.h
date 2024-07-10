#pragma once

#include "TestClass.h"	
#include "MyString.h"

class MyStringTest :
	public TestClass
{
public:
	int run() override {
		int num = 0;
		num += TestFind();
		num += TestTrim();
		num += TestSplit();

		std::cout << "测试结束，总错误个数为：" << num << std::endl;

		return 0;
	}

private:
	int TestTrim() {
		print(" ");
		int num = 0;
		print("----- 测试修剪 -----");
		MyString str = " \n a b c \t \n";
		std::cout << "字符串：" << str << std::endl;
		num += assertEqual<MyString>("a b c", str.trim());
		print(" ");

		str = "\t abc";
		std::cout << "字符串：" << str << std::endl;
		num += assertEqual<MyString>("abc", str.trim());
		print(" ");

		str = "a b c";
		std::cout << "字符串：" << str << std::endl;
		num += assertEqual<MyString>("a b c", str.trim());
		print(" ");

		str = "      ";
		std::cout << "带空格字符串：" << str << std::endl;
		num += assertEqual<MyString>("", str.trim());
		print(" ");

		str = "";
		std::cout << "空字符串：" << str << std::endl;
		num += assertEqual<MyString>("", str.trim());
		print(" ");

		std::cout << "----- 测试修剪结束，错误总个数为：" << num << "-----" << std::endl;
		print(" ");
		return num;
	}


	int TestFind() {
		print(" ");
		int num = 0;
		print("----- 测试查找 -----");
		// 寻找第一个
		print(">>> 测试1. 测试 findFirst()");
		MyString str = "123456789";
		std::cout << "字符串：" << str << std::endl;
		std::cout << "查找字符 '2'："; num += assertEqual<size_t>(1, str.findFirst('2'));
		std::cout << "查找字符 '5'："; num += assertEqual<size_t>(4, str.findFirst('5'));
		std::cout << "查找字符 '9'："; num += assertEqual<size_t>(8, str.findFirst('9'));
		std::cout << "查找字符 'a'："; num += assertEqual<size_t>(std::string::npos, str.findFirst('a'));
		std::cout << std::endl;

		str = "";
		std::cout << "空字符串：" << str << std::endl;
		std::cout << "查找字符 '2'："; num += assertEqual<size_t>(std::string::npos, str.findFirst('2'));
		std::cout << "查找字符 ' '："; num += assertEqual<size_t>(std::string::npos, str.findFirst(' '));
		std::cout << std::endl;


		// 寻找最后一个
		print(">>> 测试2. 测试 findLast()");
		str = "122333444";
		std::cout << "字符串：" << str << std::endl;
		std::cout << "查找字符 '1'："; num += assertEqual<size_t>(0, str.findLast('1'));
		std::cout << "查找字符 '3'："; num += assertEqual<size_t>(5, str.findLast('3'));
		std::cout << "查找字符 '4'："; num += assertEqual<size_t>(8, str.findLast('4'));
		std::cout << "查找字符 'a'："; num += assertEqual<size_t>(std::string::npos, str.findLast('a'));
		std::cout << std::endl;

		str = "";
		std::cout << "空字符串：" << str << std::endl;
		std::cout << "查找字符 '2'："; num += assertEqual<size_t>(std::string::npos, str.findLast('2'));
		std::cout << "查找字符 ' '："; num += assertEqual<size_t>(std::string::npos, str.findLast(' '));
		std::cout << std::endl;

		// 寻找第一个不是
		print(">>> 测试3. 测试 findFirstNot()");
		str = "122333444";
		std::cout << "字符串：" << str << std::endl;
		std::cout << "查找第一个非字符 '1'："; num += assertEqual<size_t>(1, str.findFirstNot('1'));
		std::cout << "查找第一个非字符 '1', '2'："; num += assertEqual<size_t>(3, str.findFirstNot('1', '2'));
		std::cout << "查找第一个非字符 '1', '2', '3'："; num += assertEqual<size_t>(6, str.findFirstNot('1', '2', '3'));
		std::cout << "查找第一个非字符 '1', '2', '3', '4'："; num += assertEqual<size_t>(std::string::npos, str.findFirstNot('1', '2', '3', '4'));
		std::cout << "查找第一个非字符 'a'："; num += assertEqual<size_t>(0, str.findFirstNot('a'));
		std::cout << std::endl;

		str = "";
		std::cout << "空字符串：" << str << std::endl;
		std::cout << "查找第一个非字符 '1'："; num += assertEqual<size_t>(std::string::npos, str.findFirstNot('1'));
		std::cout << "查找第一个非字符 ' '："; num += assertEqual<size_t>(std::string::npos, str.findFirstNot(' '));
		std::cout << std::endl;

		// 寻找最后一个不是
		print(">>> 测试3. 测试 findFirstNot()");
		str = "122333444";
		std::cout << "字符串：" << str << std::endl;
		std::cout << "查找最后一个非字符 '4'："; num += assertEqual<size_t>(5, str.findLastNot('4'));
		std::cout << "查找最后一个非字符 '4', '3'："; num += assertEqual<size_t>(2, str.findLastNot('3', '4'));
		std::cout << "查找最后一个非字符 '4', '3', '2'："; num += assertEqual<size_t>(0, str.findLastNot('4', '2', '3'));
		std::cout << "查找最后一个非字符 '4', '3', '2', '1'："; num += assertEqual<size_t>(std::string::npos, str.findLastNot('1', '2', '3', '4'));
		std::cout << std::endl;

		str = "";
		std::cout << "空字符串：" << str << std::endl;
		std::cout << "查找最后一个非字符 '1'："; num += assertEqual<size_t>(std::string::npos, str.findLastNot('1'));
		std::cout << "查找最后一个非字符 ' '："; num += assertEqual<size_t>(std::string::npos, str.findLastNot(' '));
		std::cout << std::endl;

		std::cout << "----- 测试查找结束，错误总个数为：" << num << "-----" << std::endl;
		print(" ");
		return num;
	}
	
	int TestSplit() {
		print(" ");
		int num = 0;
		print("----- 测试分割 -----");
		MyString str = "1,2,3,4,5";
		std::cout << "字符串：" << str << std::endl;
		std::vector<MyString> vec = str.split(',');
		std::cout << "分割结果：";
		for (auto& s : vec) std::cout << s << " ";
		std::cout << std::endl;
		num += assertEqual<size_t>(5, vec.size());
		num += assertEqual<MyString>("1", vec[0]);
		num += assertEqual<MyString>("2", vec[1]);
		num += assertEqual<MyString>("3", vec[2]);
		num += assertEqual<MyString>("4", vec[3]);
		num += assertEqual<MyString>("5", vec[4]);
		print(" ");

		str = "1,2,,3,,,4,,,,5,,,,,";
		std::cout << "字符串：" << str << std::endl;
		vec = str.split(',');
		std::cout << "分割结果：";
		for (auto& s : vec) std::cout << s << " ";
		std::cout << std::endl;
		num += assertEqual<size_t>(5, vec.size());
		num += assertEqual<MyString>("1", vec[0]);
		num += assertEqual<MyString>("2", vec[1]);
		num += assertEqual<MyString>("3", vec[2]);
		num += assertEqual<MyString>("4", vec[3]);
		num += assertEqual<MyString>("5", vec[4]);
		print(" ");

		str = ",1,2,3,4,5 ";
		std::cout << "字符串：" << str << std::endl;
		vec = str.split(',');
		std::cout << "分割结果：";
		for (auto& s : vec) std::cout << s << " ";
		std::cout << std::endl;
		num += assertEqual<size_t>(5, vec.size());
		num += assertEqual<MyString>("1", vec[0]);
		num += assertEqual<MyString>("2", vec[1]);
		num += assertEqual<MyString>("3", vec[2]);
		num += assertEqual<MyString>("4", vec[3]);
		num += assertEqual<MyString>("5 ", vec[4]);
		print(" ");
		
		str = "";
		std::cout << "空字符串：" << str << std::endl;
		vec = str.split(',');
		std::cout << "分割结果：";
		for (auto& s : vec) std::cout << s << " ";
		std::cout << std::endl;
		num += assertEqual<size_t>(0, vec.size());
		print(" ");


		std::cout << "----- 测试分割结束，错误总个数为：" << num << "-----" << std::endl;
		print(" ");
		return num;
	}
};

