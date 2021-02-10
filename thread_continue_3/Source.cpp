#include <iostream>
#include <thread>
#include <memory>

/*
	Что если я в этот поток(th_func) хочу передавать переменную а, то как это сделать?
*/

void th_func(int a) {
	std::cout << a << std::endl;
}

/*
	Что если есть класс, но в котором запрещён конструктор копирования?  ERROR
*/
	
class Debug {
public:
	Debug() = default;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = default;
};

void th_func1(Debug&& a) {  // передаю по rvalue
	std::cout << __FUNCSIG__ << std::endl;
}

void th_func2(Debug& a) {   // передаю по ссылке
	std::cout << __FUNCSIG__ << std::endl;
}

void th_func3(const Debug& a) {   // передаю по const ссылке
	std::cout << __FUNCSIG__ << std::endl;
}


int main(int args, const char* argv[]) {

	std::unique_ptr<int> ref = std::make_unique<int>(200);

	int test{ 10 };
	std::thread tr{ th_func, test }; // т.е. таким способом мы можем передавать через запятую количество тех аргументов, которая принимает наша ф-ция
									 // которая является стартовой точкой для исполнения нашего потока
	tr.join();

	Debug dbg;
	//std::thread tr1{ th_func1, dbg }; // error   .   Внутри thread создаётся некий кортеж(tuple) с аргументов(th_func1, dbg) и эти аргументы копируються
									  // в контекст этого же потока. Т.е. происходит КОПИРОВАНИЕ
	std::thread tr1{ th_func1, std::move(dbg) };

	//std::thread tr2{ th_func2, dbg }; // error   .   Надо по ссылке передавать
	std::thread tr2{ th_func2, std::ref(dbg) };
	std::thread tr3{ th_func3, std::cref(dbg) };

	tr1.join();
	tr2.join();
	tr3.join();


	return 0;
}