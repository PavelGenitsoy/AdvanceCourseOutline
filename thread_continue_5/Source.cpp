#include <iostream>
#include <thread>
#include <future>
#include <exception>


void th_func(std::promise<void> p) {
	try {
		std::this_thread::sleep_for(std::chrono::seconds(5));

		throw std::runtime_error{ "runtime_error" };
	}
	catch (const std::exception& ex) { // так всё гуд
		std::cout << "catch block\n";
	}
}


int main(int args, const char* argv[]) {

	try { 
		std::promise<void> p;
		auto fut = p.get_future();

		std::thread tr{ th_func, std::move(p) };
		tr.detach();
		//tr.native_handle(); // в данном случае native_handle это мы получаем тот ресурс, который захвачен объектом tr в конструкторе, и тупо с 
							  // ним работаем, вызывая для него какие-то определённые платформозависимые ф-ции 

		std::cout << "after run thead tr2" << std::endl;

		if (fut.wait_for(std::chrono::seconds(3)) == std::future_status::timeout) {
			std::cout << "timeout\n";
		}

		std::cout << "waited 3 seconds\n";

		fut.wait(); // wait ждёт пока ему promise не сигнализирует, что завершился. В данный контексте пока не завершится поток tr

		std::cout << "and still waited 2 seconds\n";
	}
	catch (const std::runtime_error& ex) {  // всё равно будет вызван terminate and then abort. Кинутое исключение с одного потока не может быть 
											// перехвачено в контексте другого  (стеки у них же разные, а происходит раскрутка стека)
											// поэтому надо try catch ставить в каждом потоке тогда (в данном случае там где кидается исключение)
											// но всё же хотелось уметь перехватывать exception в 1 потоке и передавать в другой, и обрабатывать
	}


	return 0;
}