#include <iostream>
#include <exception>


/*
	noexcept - это гарантия того, что ф-ция или метод не вызовут exception.

	Надо стараться помечать конструктора как noexcept это хорошое правило. 
*/


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }

	~Debug() { std::cout << __FUNCSIG__ << std::endl; }

	void print() noexcept { 
		std::cout << __FUNCSIG__ << std::endl; 
		throw std::runtime_error{ "test" }; // if exception -> abort.  Здесь не будет раскрутки стека , а сразу будет прерывание
	}

	void print_() {
		std::cout << __FUNCSIG__ << std::endl;
		throw std::runtime_error{ "runtime_error" }; 
	}

	void some_method() noexcept {
		std::cout << __FUNCSIG__ << std::endl;
		try {
			print_();
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}

	/*
		Можно делать noexcept с какими-то условиями 
	*/

	//void method1() noexcept(RAII()) { // в данном случае будет noexcept, только в том случае, если раишный конструктор не будет кидать exception
	//	RAII r;
	//	//... some code
	//}


};


int main(int args, const char* argv[]) {

	Debug d{ "main" };

	// d.print(); // так как стоит noexcept, то и смысла в try catch заворачивать нет!

	d.some_method(); // так всё гуд





	system("pause");
	return 0;
}