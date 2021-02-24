#include <iostream>
#include <vector>
#include <array>
#include <initializer_list> 


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&&) noexcept { std::cout << __FUNCSIG__ << std::endl; } // noexcept гарантирует exception safe
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&&) { return *this; }
};


int main(int argc, const char* argv) {

	std::array<Debug, 5> arr;
	std::vector<Debug> v; 
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;

	// v.push_back(Debug{ 1 }); // произошла перегрузка с rvalue
	// std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;
	/*
		Output:
			size:0  capacity:0
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&)
			__thiscall Debug::~Debug(void)
			size:1  capacity:1
			__thiscall Debug::~Debug(void)


			тут можно увидеть что лишнее это вызов перемещающего конструктора и деструктора для временного объекта, ибо это ненужный объект. Поэтому  
			вектор предоставляет другой метод emplace_back (конструирование на месте), он важен когда вектор содержит пользовательские типы.
	*/

	v.emplace_back(1);
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;
	/*
		Output:
			size:0  capacity:0
			__thiscall Debug::Debug(int)
			size:1  capacity:1

		Нет создания временного объекта! Также emplace_back под капотом может делать push_back - (v.emplace_back(Debug{1}))
	*/

	v.push_back(Debug{ 1 }); 
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;
	/*
		Output:
			size:0  capacity:0
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&)
			__thiscall Debug::~Debug(void)
			size:1  capacity:1
			__thiscall Debug::Debug(int)  // снова всё тоже самое(конструируется временный объект)
			__thiscall Debug::Debug(class Debug &&)   // для него вызывается конструктор перемещения. 
			__thiscall Debug::Debug(const class Debug &) // НО тут уже вызывается конструктор копирования. Вызывается тогда когда происходит 
														 // переаллокация (size=2, a capacity=1). Мы увеличиваем ёмкость и копируем старый сконструированный
														 // объект в новый
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			size:2  capacity:2
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/

	v.push_back(Debug{ 1 });
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;
	/*
		Output:
			size:0  capacity:0
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&)
			__thiscall Debug::~Debug(void)
			size:1  capacity:1
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			size:2  capacity:2
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			size:3  capacity:3
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)

		Проблема в том, что мы постоянно постоянно копируем и разрушаем объекты. Поэтому добавим noexcept в конструктор перемещения. И будем использовать
		перемещение, вместо копирования.

		Output (after noexcept):
			size:0  capacity:0
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::~Debug(void)
			size:1  capacity:1
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			size:2  capacity:2
			__thiscall Debug::Debug(int)
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::Debug(class Debug &&) noexcept
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			size:3  capacity:3
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/

	v.clear();  // ёмкость не очистит!  Тут принудительно вызываем деструктора на объектов которые содержатся в векторе
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl;  // size:0  capacity:3

	v.shrink_to_fit();
	std::cout << "size:" << v.size() << "\tcapacity:" << v.capacity() << std::endl; // size:0  capacity:0   (уменьшает ёмкость до размеры size вектора)

	
	v.reserve(arr.size()); // всегда надо делать перед тем как будем что-то циклическое делать с вектором (добавление элементов). Выделяем память.
	for (const auto& value : arr)
	{
		v.push_back(value);
	}
	/*
		Output (without reserve):
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::Debug(const class Debug &)
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::Debug(class Debug &&) noexcept
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)
		__thiscall Debug::~Debug(void)


		Output (with reserve):
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::Debug(const class Debug &)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
			__thiscall Debug::~Debug(void)
	*/


	return 0;
}