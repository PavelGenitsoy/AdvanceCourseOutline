#include <iostream>
#include <vector>
#include <array>
#include <initializer_list> // эта сущность нужна чтобы что-то с чем-то инициализировать


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&&)noexcept { std::cout << __FUNCSIG__ << std::endl; }
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&&) { return *this; }
};


void func(std::initializer_list<int> il) { // его проблема что он является однотипным, но это можно обойти используя any
	for (auto &&i: il)
	{

	}
}


int main(int argc, const char* argv) {

	/*std::array<Debug, 5> ar;
	std::vector<Debug> v{ar.begin(), ar.end()};*/  // можно так инициализировать

	// std::vector<Debug> v(2);  // так делать не очень хорошо, ибо если будем работать с его элементами то будут вызыватся конструктора(а они могут весомые быть)
								// дефолтная инициализация
	/*
		Output: 
			__thiscall Debug::Debug(void)
			__thiscall Debug::Debug(void)
			2
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/

	// std::vector<Debug> v{ Debug{1}, Debug{2, 2.4}}; // специфическая инициализация
	/*
		Output:
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(int,double)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			2
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/

	std::vector<Debug> v{2}; // тут сработало неявное преобразование int в объект класс Дебаг
	/*
		Output:
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::~Debug(void)   // деструктор для временного объекта
			1
			__thiscall Debug::~Debug(void)


		Output (after added explicit before constuctor): // в этом случае также лучше не использовать универсальну инициализацию {}, а лучше такую () 
			__thiscall Debug::Debug(void)
			__thiscall Debug::Debug(void)
			2
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/
	std::cout << v.size() << std::endl;






	return 0;
}