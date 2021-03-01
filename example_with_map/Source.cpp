#include <iostream>
#include <map>
#include <string>


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) : value_{ value } { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&& rhs)noexcept { // делали перегрузку для insert_or_assign
		value_ = rhs.value_;
		std::cout << __FUNCSIG__ << std::endl;
	}
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&& rhs) { // делали перегрузку для insert_or_assign
		value_ = rhs.value_;
		return *this;
	}

	int value() const {
		return value_;
	}

	void set_value(int new_value) {
		value_ = new_value;
	}
private:
	int value_{};
};


bool operator < (const Debug& lhs, const Debug& rhs) {
	return lhs.value() < rhs.value();
}


Debug getFileCash(const char* file_name) {
	static std::map<std::string, Debug> cash; // std::string будет представлять собой имя файла и по нему будем содержать данные
	/*
	auto value = cash[file_name]; // эта форма опасна тем, что если ключа нету который мы проверяем, то она создаст ноду с дефолтным этим ключём и дефолтным значением
								  // в нашем случае мы сконструируем ноду, которая будет содержать string, которая будеть содержать пустой Debug
								  
	if (value.value() == 0) {
		std::cout << "open file\n";
		// read from file_name

		cash[file_name] = std::move(value);  // плохая форма
	}

	return value;
	


	Output: 
		__thiscall Debug::Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		open file
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		open file
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
	*/
								  // поэтому всегда лучше find для проверки существования ключа

	auto it{ cash.find(file_name) };
	//Debug value{ 5 }; // for example
	if (it == cash.end()) {
		std::cout << "open file\n";
		// read from file_name

		cash.emplace(file_name, Debug{5});
	}

	/*
	Output:
		open file
		__thiscall Debug::Debug(int)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::~Debug(void)
		open file
		__thiscall Debug::Debug(int)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
	*/

	return cash[file_name]; 
}


int main(int argc, const char* argv) {

	getFileCash("1.txt");
	getFileCash("2.txt");


	return 0;
}