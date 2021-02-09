#include <iostream>
#include <thread>


void th_func() {
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "Hello from function" << std::endl;
}


int main(int args, const char* argv[]) { 

	std::thread tr{ []() {
		std::cout << "Hello from lambda" << std::endl;  
	} };

	std::cout << "Hello from main" << std::endl;

	std::thread tr1{ th_func };

	tr1.detach(); // мы никогда не увидим "Hello from function". Почему? Ибо когда мы делаем detach, то мы не дожидаемся завершение этих потоков
	tr.detach();

	std::cout << "after thread execution" << std::endl;



	return 0;
}