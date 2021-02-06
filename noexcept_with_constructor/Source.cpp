#include <iostream>
#include <exception>
#include <vector>


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug& rhs) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&& rhs) { std::cout << __FUNCSIG__ << std::endl; }
};


class Debug_ {
public:
	Debug_(const char* log) { std::cout << log << std::endl; }
	~Debug_() { std::cout << __FUNCSIG__ << std::endl; }
	Debug_(const Debug& rhs) { std::cout << __FUNCSIG__ << std::endl; }
	Debug_(Debug&& rhs) noexcept { std::cout << __FUNCSIG__ << std::endl; }
};


int main(int args, const char* argv[]) {

	std::vector<Debug> v;

	v.emplace_back("1");
	v.emplace_back("2");
	v.emplace_back("3");
	v.emplace_back("4");

	/*
	Output:
		1
		2
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::~Debug(void)  // деструктор для 1
		3
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		4
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)


		Vector это динамический массив с возможностью внутренней переалокацией. Вектор делает некую реалокацию и, в процессе реалокации, 
		он старое значение копирует в новую память.

		И возникает вопрос почему компилятор делает копирование, если есть явный конструктор перемещения??

		Ибо вектор использует понятие инварианта. Ибо если в процессе копирование у вас произойдёт exception (конструктор копирования его 
		кинет), то по сути старый объект на разрушился, а новую память под новый объект не смогли выделить (инвариант не нарушается).
		Если бы мы использовали конструктор перемещения и сработал exception, то новый объект не получилось создать, а в старом объекте 
		значение уже не валидно, ибо это семантика move такая... и тогда нарушается инвариант! 

		И чтобы дать гарантию компилятору, что exception точно не будет, то помечаем конструктор перемещения noexcept
	*/

	std::cout << "/////////////////////////////\n";

	std::vector<Debug_> v_;

	v_.emplace_back("1");
	v_.emplace_back("2");
	v_.emplace_back("3");
	v_.emplace_back("4");

	/*
	Output:
		1
		2
		__thiscall Debug_::~Debug_(void)
		3
		__thiscall Debug_::~Debug_(void)
		__thiscall Debug_::~Debug_(void)
		4
		__thiscall Debug_::~Debug_(void)
		__thiscall Debug_::~Debug_(void)
		__thiscall Debug_::~Debug_(void)
	*/



	system("pause");
	return 0;
}