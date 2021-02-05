#include <iostream>
#include <exception>


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }

	~Debug() { std::cout << __FUNCSIG__ << std::endl; }

	void print() { std::cout << __FUNCSIG__ << std::endl; }
};


void generate_exception() {
	throw std::runtime_error{ "runtime_error" }; 
	std::cout << "end void generate_exception\n";
} 


void call_exception_old() {
	Debug* ptr = new Debug{__FUNCSIG__};  // конструктор вызовится , но деструктор нет, т.е. утечка ресурсов

	generate_exception();

	delete ptr; // этот делит никогда не выполним
	std::cout << "end void call_exception\n";
}


class RAII {  // раньше юзали такие рукописные смарт-поинтеры
public:
	RAII(Debug* ptr) { std::cout << "RAII ctr\n"; }

	~RAII() { // delete 
		std::cout << "RAII dtr\n"; }
};


class RAII_ {  
public:
	RAII_() { std::cout << "RAII_ ctr\n"; }

	~RAII_() { std::cout << "RAII_ dtr\n"; }
};


void call_exception_old_but_newer() {
	RAII raii{ new Debug{ __FUNCSIG__ } };  

	generate_exception();

	std::cout << "end void call_exception\n";
}


void call_exception_new() {
	std::unique_ptr<Debug> ptr{ std::make_unique<Debug>( __FUNCSIG__ ) };  // если бы не нашёлся catch блок, то деструктор бы не вызвался!!!

	generate_exception();

	std::cout << "end void call_exception\n";
}


void call_exception_new_1() {
	RAII_ raii;

	call_exception_new();

	std::cout << "end void call_exception\n";
}


int main(int args, const char* argv[]) {

	try {
		// call_exception_old();   // memory leak
		// call_exception_old_but_newer();
		// call_exception_new(); // всё гуд как и надо делать, но тоже есть 1 подводный камень с которым надо быть внимательным
		call_exception_new_1();
	}
	catch (std::runtime_error& ex) {	
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception& ex) {  
		std::cout << ex.what() << std::endl;
	}
	catch (...) { 
		std::cout << "generic error\n";
	}

	std::cout << "continue main_func\n";


	system("pause");
	return 0;
}