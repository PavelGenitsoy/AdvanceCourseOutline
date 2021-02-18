#include <iostream>
#include <thread>


int value{ 10 };
bool flag{ false };


/*
	1) Явный пример data racing. У нас 2 потока одновременно обращаемся к (памяти) переманной flag, в 1 месте read, а в другом write

	2) Происходит оптимизация при компилировании, т.е. например компилятор сам в условии while поставил True, и это race condition



	Чтобы их не было, будем использовать мьютекс как механизм синхронизации.
	mutex подразумевает понятия захвата(acquire) и освобождения(realise).   Мьютекс должен быть общим между обьектами потоков
*/

void produce() {
	value = 100;

	flag = true;
}


void consume() {
	while (flag = false)	{
		;  // тут будем простаивать
	}

	std::cout << value << std::endl;
}


int main(int args, const char* argv[]) {

	std::thread tr1{ consume };  
	std::thread tr2{ produce };

	// по идее должно было залипнуть в цикле

	tr1.join();
	tr2.join();



	return 0;
}