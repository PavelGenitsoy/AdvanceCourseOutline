#include <iostream>
#include <thread>
#include <future>
#include <exception>


std::exception_ptr eptr;

void func() {
	throw std::runtime_error{ "runtime_error" };
}


int th_func() {    //  теперь же мы можем использовать эту ф-цию как в многопоточном коде(через async), также можем вызывать как обычную ф-цию
	std::cout << "some log th_func" << std::endl;
	
	std::cout << std::this_thread::get_id() << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));

	// func();  // также async хендлят у себя exception
	
	return 10;
}


int main(int args, const char* argv[]) {
	try {
		//auto fut = std::async(th_func);  // результатом async являеться future

		//std::cout << fut.get() << std::endl;  // если было кинуто исключение, то тут будет использован механизм rethrow_exception



		/*
		НО future async-ка имеет ньюанс: у него есть launch_policy.   Также она у себя в деструкторе неявно делает wait() и соответственно мы тупо
		блокируемся пока какой-то поток не завершится
		*/


		std::cout << std::this_thread::get_id() << std::endl; 
		/* 
			По айди увидим что ф-ция th_func вызывается в одном и том же потоке (изза deferred).  

			deferred удобно использовать если мы делаем что-то с раишной концепцией, типа при выходе из области видимости future будет вызван wait()
			и тем самым будет вызвана какае-то ф-ция очистки ресурсов(например).
		*/
		auto fut1 = std::async(std::launch::deferred, th_func); // deferred  (отложенный запуск)  означает, что th_func будет вызвана тогда, когда 
																// вызовем get() or wait()
		
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::cout << "some log fut1 main " << std::endl;

		std::cout << fut1.get() << std::endl;





		std::cout << std::this_thread::get_id() << std::endl;
		/*
			По айди увидим что ф-ция th_func вызывается в разных  потоках (изза async)
		*/
		auto fut2 = std::async(std::launch::async, th_func);

		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::cout << "some log fut2 main" << std::endl;

		std::cout << fut1.get() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	


	return 0;
}