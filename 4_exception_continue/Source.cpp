#include <iostream>
#include <exception>


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }

	~Debug() { std::cout << __FUNCSIG__ << std::endl; }

	void print() { std::cout << __FUNCSIG__ << std::endl; }
};


/*
	Что ж будет если мы создаём динамический массив объектов RAII??
*/


class RAII {
public:
	RAII() {
		std::cout << "RAII ctr\n";
		if (value++ > 4)
		{
			throw std::bad_alloc{};
		}
	}

	~RAII() { std::cout << "RAII dtr\n"; }
private:
	static inline int value{0};
};


// int RAII::value{ 0 }; // можно так не определять, а юзать inline, которые появились в С++17


void call_exception_new() {
	// RAII* ptr = new RAII[10];
	std::unique_ptr<RAII[]> ptr{ new RAII[10] {} }; // создали 5 объектов и шестой кинул исключение. Т.е. для пяти первых объектов выделили 
	// память и в этой памяти создали объекты, а на шестом объекте произошло исключение. Т.е. мы не до конца отработали выражение. И
	// компилятор говорит: что если эта конструкция не была завершена, то и не будет memory leak. Гарантировано будет вызвано 5 деструкторов.

	std::cout << "end void call_exception_new\n";
}


void call_exception_new_1() {
	try {
		call_exception_new();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << "end void call_exception_new_1\n";
}


int main(int args, const char* argv[]) {

	call_exception_new_1();
	std::cout << "main\n";


	system("pause");
	return 0;
}