#include <iostream>
#include <exception>


class Debug {
public:
	Debug(const char* log) { std::cout << log << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug& rhs) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&& rhs) noexcept { std::cout << __FUNCSIG__ << std::endl; }
};


void throw2() {
	std::cout << __FUNCSIG__ << std::endl;
	throw std::runtime_error{ "runtime_error" };
}

/*
	Решили добавить stack trace (чтобы больше понимать природу ошибки). Это когда между вызовами мы добавляем какое-то логирование. 

	Хотелось бы получить какое-то логирование, но проблема в том, что throw1 это промежуточная ф-ция, а не завершённая.
*/

void throw1() {
	try {
		throw2();
	}
	// сквозные кетчи
	catch (const std::exception& ex) {  // я хочу этот exception прокинуть дальше по стеку (уже в мейн), т.е. здесь его только залогировать
		std::cout << __FUNCSIG__ << std::endl;
		//throw ex; // есть такой вариант прокида дальше, но есть ПРОБЛЕМА: в этой строке мы не кидаем тот же объект exception, который
					// сгенерировался в throw2, а создаём новый объект exception типа std::exception, а не типа std::runtime_error

		throw; // вот правильный вариант, где мы исходный объект exception проталкиваем по стеку до мейна
	}
}


int main(int args, const char* argv[]) {

	try {
		throw1();
	}
	catch (const std::exception& ex) {
		std::cout << __FUNCSIG__ << std::endl;
		std::cout << ex.what() << std::endl;
	}



	system("pause");
	return 0;
}