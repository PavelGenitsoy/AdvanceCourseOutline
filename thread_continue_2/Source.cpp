#include <iostream>
#include <thread>
#include <memory>


void th_func() {
	std::cout << "Hello from function" << std::endl;
}


//std::unique_ptr<int> ref;  // если мы объявляем глобальную переменную, то в лямбде мы не должны её захватывать, она автоматическии будет глобальна
						   // по отношению ко всем лямбда


int main(int args, const char* argv[]) {

	//ref = std::make_unique<int>(200);
	std::unique_ptr<int> ref = std::make_unique<int>(200);

	std::thread tr{ [/*&ref*/ ref1 = std::move(ref)]() {
		std::cout << "Hello from lambda" << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(1));

		//*ref = 100; // UB 
		*ref1 = 100;
		/*
			Почему UB? 
				У нас создана какае-то глобальная переменная (ref) и есть объект потока. Но проблема, если мы делаем для потока detach, то объект
				потока может ещё исполняться, когда уже нету этой глобальной переменной. Т.е. у нас уже объекта ref может уже не существовать, но 
				поток может ещё исполнять код, и мы обращаемся к переменной, которая являеться висячей ссылкой.

				С локальной ref тоже самое. Наш поток(tr) явно переживает жизнь потока main. Т.е. у нас основной поток завершиться, его стек разрушиться.
				И мы будем обращаться к локальной переменной, которой уже не существует.

				т.е. то что мы отпустили в detach, то объект должен иметь его локальный state. он ничего не должен брать с внешнего контекста!!
				в поток лучше передавать копию чего-то, а в нашем случае замувать его
		*/
	} };

	std::cout << "Hello from main" << std::endl;

	std::thread tr1{ th_func };

	tr1.join();

	//.........
	tr.detach();

	std::cout << "after thread execution" << std::endl;





	return 0;
}