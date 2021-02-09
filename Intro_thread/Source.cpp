#include <iostream>
#include <thread>


/*
	Все потоки являються объектами std::thread. И входным параметром мы должны передать точку исполнения нашего потока(т.е. всё что ведёт себя
	как ф-ция)
*/


void th_func() {
	std::cout << "Hello from function" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
}


int main(int args, const char* argv[]) { // main ф-ция которая определяет жизненный цикл основного потока

	std::thread tr{ []() {
		std::cout << "Hello from lambda" << std::endl;  // иногда выполнение этой задачи может происходить позже, всё от загружености ядер процессора
	}};

	std::cout << "Hello from main" << std::endl;

	std::thread tr1{ th_func };

	tr1.join(); // join(), это значит что мы разрываем связь объекта std::thread с тем потоком (что ресурс содержит) с которым он был связан.
	tr.join();  // в join мы блокируемся до тех пор, пока ваша ф-ция связаная с этим объектом потока не завершит своё выполнение


	std::cout << "after thread execution" << std::endl;



	return 0; 
}