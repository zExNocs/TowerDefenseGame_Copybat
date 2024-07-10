#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <cstring>
#include <string>
#include <vector>

class MyString {
public:
	MyString() = default;

	MyString(const std::string& str) : myString(str.begin(), str.end()) {}

	MyString(const char* cstr) : myString(cstr, cstr + std::strlen(cstr)) {}

	MyString(const std::vector<char>& vecstr) { this->myString = vecstr; }

	~MyString() = default;

public:


public:
	// ---------------- 类型转化函数 ----------------
	std::string to_string() const { return std::string(myString.begin(), myString.end()); }

	const std::vector<char> data() const { return myString; }

	const char* to_cstr() const { return myString.data(); }

public:
	// ---------------- 功能函数 ----------------
	/* 是否为空 */
	bool empty() const { return myString.empty(); }

	/* 获取长度 */
	size_t length() const { return myString.size(); }

	/* 删除全部指定的字符 */
	void removeAll(char c) {
		myString.erase(std::remove(myString.begin(), myString.end(), c), myString.end());
	}

	/* 删除全部 多个字符 */
	template<typename... Args>
	typename std::enable_if<std::conjunction<std::is_same<Args, char>...>::value>::type
	removeAll(char c, Args... args) {
		removeAll(c);

		std::vector<char> toRemove = { args... };
		for (char arg : toRemove) removeAll(arg);
	}

	/* 删除第一个指定的字符。删除成功返回 true，否则返回 false */
	bool removeFirst(char c) {
		auto it = std::find(myString.begin(), myString.end(), c);
		if (it == myString.end()) return false;

		myString.erase(it);
		return true;
	}

	/* 删除最后一个指定的字符。删除成功返回 true，否则返回 false */
	bool removeLast(char c) {
		auto it = std::find(myString.rbegin(), myString.rend(), c);
		if (it == myString.rend()) return false;

		myString.erase((it + 1).base());
		return true;
	}

	/* 找到第一个指定字符的位置。没找到则返回 npos。*/
	size_t findFirst(char c) const {
		if (myString.empty()) return std::string::npos;

		auto it = std::find(myString.begin(), myString.end(), c);
		if (it == myString.end()) return std::string::npos;

		return std::distance(myString.begin(), it);
	}

	/* 找到最后一个指定字符的位置。没找到则返回 npos。*/
	size_t findLast (char c) const {
		if (myString.empty()) return std::string::npos;

		auto it = std::find(myString.rbegin(), myString.rend(), c);
		if (it == myString.rend()) return std::string::npos;

		return myString.size() - 1 - std::distance(myString.rbegin(), it);
	}

	/* 找到第一个非指定的字符集。没找到则返回 npos。*/
	template<typename... Args>
	typename std::enable_if<std::conjunction<std::is_same<Args, char>...>::value, size_t>::type
	findFirstNot(Args... args) const {
		if (myString.empty()) return std::string::npos;
		std::vector<char> charList = { args... };

		size_t size = myString.size();
		size_t index = 0;

		char this_c = get(index);
		bool flag = false;
		for (char found_c : charList) flag |= (this_c == found_c);
		while (index < size - 1 && flag) {
			index++;
			this_c = get(index);
			flag = false;
			for (char found_c : charList) flag |= (this_c == found_c);
		}
		
		if (index == size - 1 && flag) return std::string::npos;
		return index;
	}

	/* 找到最后一个非指定的字符集。没找到则返回 npos。*/
	template<typename... Args>
	typename std::enable_if<std::conjunction<std::is_same<Args, char>...>::value, size_t>::type
	findLastNot(Args... args) const {
		if (myString.empty()) return std::string::npos;
		std::vector<char> charList = {args... };

		size_t index = myString.size() - 1;

		char this_c = get(index);
		bool flag = false;
		for (char found_c : charList) flag |= (this_c == found_c);
		while (index > 0 && flag) {
			index--;
			this_c = get(index);
			flag = false;
			for (char found_c : charList) flag |= (this_c == found_c);
		}
		if (index == 0 && flag) return std::string::npos;
		return index;
	}

	/* 根据index获取字符 */
	char get(size_t index) const { return myString[index]; }

	/* 添加字符 */
	void push(char c) { myString.push_back(c); }

	/* 清理容器 */
	void clear() { myString.clear(); }

	/* 子字符串 */
	MyString substr(size_t index, size_t length) const {
		size_t size = myString.size();
		if (myString.empty() || length <= 0 || index >= size) return MyString();
		
		// 修剪index
		if (index < 0) index = 0;

		// 修剪length
		if (index + length > size) length = size - index;

		std::vector<char> temp(myString.begin() + index, myString.begin() + index + length);
		return MyString(temp);
	}

	/* 修剪该字符串，不改变原有字符串。返回前后不具有空格、换行和tab的版本。 */
	MyString trim() const {
		size_t begin_idx = findFirstNot(' ', '\t', '\n');
		if (begin_idx == std::string::npos) return MyString();
		size_t end_idx = findLastNot(' ', '\t', '\n');
		size_t idx_range = end_idx - begin_idx + 1;

		return substr(begin_idx, idx_range);
	}

	/* 分割字符串 */
	std::vector<MyString> split(char c) {
		std::vector<MyString> vecStr;
		MyString splited;

		for (char data : myString) {
			if (data == c) {
				if (!splited.empty()) vecStr.push_back(splited);
				splited.clear();
			} else {
				splited.push(data);
			}
		}
		if(!splited.empty()) vecStr.push_back(splited);
		return vecStr;
	}


public:
	// ---------------- 运算符 ----------------
	/* 重载输出运算符 */
	friend std::ostream& operator<< (std::ostream& os, const MyString& point);

	/* 加等于 */
	MyString& operator+= (const MyString& rhs) {
		myString.insert(myString.end(), rhs.data().begin(), rhs.data().end());
		return *this;
	}

	/* 加法：同类 */
	MyString operator+ (const MyString& rhs) const {
		MyString tempLHS = *this;
		return tempLHS += rhs;
	}

	/* 加法：字符串 + */
	friend MyString operator+ (const std::string& lhs, const MyString& rhs) {
		MyString tempLHS(lhs);
		return tempLHS + rhs;
	}

	/* 等于 */
	MyString& operator= (const MyString& rhs) {
		myString = rhs.data(); 
		return *this;
	}

	/* 等于等于 */
	bool operator== (const MyString& rhs) const {
		size_t size = length();
		if (size != rhs.length()) return false;

		for (size_t i = 0; i < size; i++) if (myString[i] != rhs.get(i)) return false;
		return true;
	}

private:
	std::vector<char> myString;

};


// 输出运算符重载的实现
inline std::ostream& operator<< (std::ostream& os, const MyString& str) {
	os << str.to_string();
	return os;
}

#endif // !_MY_STRING_H_