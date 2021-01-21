#include <iostream>


class String {
public:
	String() = default;
	String(int size) { std::cout << __FUNCSIG__ << std::endl; }
	String(const char* str) { std::cout << __FUNCSIG__ << std::endl; }
	String(int count, char ch) { std::cout << __FUNCSIG__ << std::endl; }
	String(const String&) { std::cout << __FUNCSIG__ << std::endl; }
	String(String&&) { std::cout << __FUNCSIG__ << std::endl; }
	String operator =(const String&) { std::cout << __FUNCSIG__ << std::endl; return *this; }
	String operator =(String&&) { std::cout << __FUNCSIG__ << std::endl; return *this; }
};

template <typename T>
class Cont {
public:
	void push(const T& string) {
		arr[0] = string;
	}

	void push(T&& string) {   // здесь не универсальная ссылка, а как обычная rvalue reference
		arr[0] = std::move(string);
	}

	template <typename U>		// напишем emplace, чтобы конструировать объект на месте. Т.е. мы не будем создавать временный об., потом перемещать и т.д.
	void emplace(U&& data) {			// здесь уже универсальная ссылка
		new(&arr[0]) String{ data };		// ((arr + 0) or &arr[0] or &arr) это всё одно и тоже. оператор new указывает, что на этом &arr[0] адрессе, просто вызови конструктор
	}

private:
	T arr[10];	
};

int main(int argc, const char *argv[]) {
	Cont<String> cnt;
	// String str("hello");		// тут много всего делаем,
	// cnt.push(str);           // а хотелось бы сразу на месте всё оформить
	// cnt.push(String{10});	   

	cnt.emplace(10);

	system("pause");
	return 0;
}