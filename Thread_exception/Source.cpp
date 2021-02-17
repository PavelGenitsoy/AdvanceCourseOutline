#include <iostream>
#include <thread>
#include <future>
#include <exception>


/*
	Способ (std::exception_ptr eptr   and   std::current_exception()) как отлавливать exception в одних потоках и передавать в мейн поток
*/


std::exception_ptr eptr;

void func() {
	throw std::runtime_error{ "runtime_error" };
}


void th_func(std::promise<void> p) {   // хотелось бы эту ф-цию использовать в контексте потоков так и без потоков.  Всё это делают async
	std::this_thread::sleep_for(std::chrono::seconds(1));

	try {
		func();
	}
	catch (const std::exception& ex) {
		eptr = std::current_exception();  // отхватили exception
	}
}


int main(int args, const char* argv[]) {
	try {
		std::promise<void> p;
		auto fut = p.get_future();

		std::thread tr{ th_func, std::move(p) };
		tr.detach();

		std::cout << "after run thead tr2" << std::endl;

		fut.wait();

		std::rethrow_exception(eptr);  //  пробросили exception
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}