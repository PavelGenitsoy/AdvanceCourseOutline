#include <iostream>
#include <thread>
#include <atomic>


std::atomic<bool> flag = false;  // в шаблоне указываем тип памяти которую мы хотим сделать атомарной. Будем работать с переменной flag будто она булевая(не 
						 //	имея lock/unlock), но в контексте синхронизации, т.е. тем самым избегаем data race, это первый момент! А второй: нужно, 
						 // перед тем как работать с атомиком, проверить имеет ли ваш cpu встроенные инструкции для работы с lock_free, если не умеет,
						 // то будет обычный мьютекс(ибо атомик под капотом мьютекс)
std::atomic<int> value = 10;


void produce() {
	value = 100;
	flag = true;
}


void consume() {
	while (not flag) {
		;
	}

	std::cout << value << std::endl;
}



int main(int args, const char* argv[]) {

	std::thread tr1{ consume };
	std::thread tr2{ produce };


	tr1.join();
	tr2.join();



	return 0;
}