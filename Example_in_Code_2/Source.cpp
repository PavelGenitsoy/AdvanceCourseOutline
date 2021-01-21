#include <iostream>


class B {
public:
	B() = default;
	B(const B&) { std::cout << __FUNCSIG__ << std::endl; }
	B(B&&) { std::cout << __FUNCSIG__ << std::endl; }
	B& operator =(const B&) { std::cout << __FUNCSIG__ << std::endl; return *this; }
	B& operator =(B&&) { std::cout << __FUNCSIG__ << std::endl; return *this; }
	~B() { std::cout << __FUNCSIG__ << std::endl; }
};

class String {
public:
	String() = default;

	String(B& data) { std::cout << __FUNCSIG__ << std::endl; }
	String(B&& data) { std::cout << __FUNCSIG__ << std::endl; }

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

	void push(T&& string) {  
		arr[0] = std::move(string);
	}

	/*
	template <typename U>		
	void emplace1(U&& data) {			
		new(&arr[0]) String{data};		// а в итоге data будет lvalue, ибо data это именованный объект
	}
	*/

	template <typename U>
	void emplace(U&& data) {
		new(arr + 0) String{ std::forward<U>(data) };
	}

private:
	T arr[10];
};

int main(int argc, const char *argv[]) {
	Cont<String> cnt;   

	// cnt.emplace1(10); // так норм
	
	// cnt.emplace1(B{}); // передаём как rvalue в emplace, а в итоге...(смотреть на emplace, которая закомментирована)
	
	B b;

	cnt.emplace(B{}); 
	cnt.emplace(b);

	system("pause");
	return 0;
}