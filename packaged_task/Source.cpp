#include <iostream>
#include <thread>
#include <future>
#include <exception>


void func() {
	throw std::runtime_error{ "runtime_error" };
}


int th_func() {   
	std::cout << "some log th_func" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(50));  // поставили такой слип и увидели, что мы теперь не дожидаемся завершения этого потока

	func(); 

	return 10;
}


int main(int args, const char* argv[]) {
	try {
		std::cout << std::this_thread::get_id() << std::endl;

		
		std::packaged_task<int()>pt{ th_func };  // packaged_task (некий врапер) просто обворачивает ф-цию th_func, добавляя у неё внутри механизм promise-future 
												 // и умеет хендлить эксепшн. Сама по себе packaged_task делает rethrow_exception
												 // { try {prommise func(); promise.setvalue()} catch() {}}
		
		auto fut = pt.get_future();  // теперь эта future ведёт себя как обычная future, не вызывая у себя в деструкторе wait

		std::thread { std::move(pt) }.detach();

		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::cout << "some log fut main " << std::endl;

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}




	return 0;
}