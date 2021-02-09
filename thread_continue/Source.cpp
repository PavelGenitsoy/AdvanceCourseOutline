#include <iostream>
#include <thread>


/*
	Каждый поток имеет свой ID. Он каждый раз при исполнении кода, как-то себя уникально идентифицирует
*/


void th_func() {
	std::cout << std::this_thread::get_id() << std::endl;  // это чисто для логирования  (удобность механизма) но чтоб точно знать какой ID к какому
														   // потоку то использовать надо механизмы синхронизации (мьютексы к примеру)
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Hello from function" << std::endl;
}


int main(int args, const char* argv[]) {

	std::cout << std::thread::hardware_concurrency() << std::endl; // должно вывести сколько у меня возможных(там точность под 99%) физических потоков

	std::cout << std::this_thread::get_id() << std::endl;

	std::thread tr{ []() {
		std::cout << std::this_thread::get_id() << std::endl;
		std::cout << "Hello from lambda" << std::endl;
	} };

	std::cout << "Hello from main" << std::endl;

	std::thread tr1{ th_func };

	//std::thread tr2 = tr1;  // ошибка так как нету конструктора копирования, а только перемещения (похоже на идеологию unique_ptr)

	// tr1.detach(); // будет исключение, мы не можем повторно с одним и тем же объектом то же самое или (detach) сделать. Ибо в этой строке tr1 уже не
					 // владеет информацией о том потоке, который ранее был им запущенный.  Поэтому всегда рекомендуеться делать проверку на joinable!!!

	if (tr1.joinable()) {  // если tr1 имеет связь с потоком , то..
		tr1.join();
	}

	if (!tr1.joinable()) {
		std::cout << "not joinable" << std::endl;
	}
	
	tr.join();

	std::cout << "after thread execution" << std::endl;

	



	return 0;
}