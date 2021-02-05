#include <iostream>
#include <exception>


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }

	~Debug() { std::cout << __FUNCSIG__ << std::endl; }

	void print() { std::cout << __FUNCSIG__ << std::endl; }
};


/*
	Сделаем так чтобы exception кидало в конструкторе класса RAII.  

	И получится так, что деструктор вызыватся не будет, ибо по факту сам объект мы так и не сконструировали!

	И считается правильным юзкейсом кидать исключение в конструктор, тем самым мы гарантируем, что деструктор не будет вызван. Это 
	единственный способ сообщить об ошибке во время конструирования объекта. 	
*/


class RAII {  
public:
	RAII() { 
		std::cout << "RAII ctr\n";
		throw std::bad_alloc{};
	}

	~RAII() { std::cout << "RAII dtr\n"; }
};



void call_exception_new() {
	std::unique_ptr<RAII> ptr{ std::make_unique<RAII>() };  // деструктора не будет, ибо мы не создали полноценный объект RAII

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