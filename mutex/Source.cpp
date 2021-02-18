#include <iostream>
#include <thread>
#include <mutex>
#include <queue>


int value{ 10 };
bool flag{ false };

std::mutex mt;
std::queue<int> q;

void produce() {
	/*  // часть с прошлого примера (начало в предыдущем проекте)
	mt.lock();
	value = 1000;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	mt.unlock();
	*/

	static int i{}; // глобальная инициализция по отношение к ф-ции
	while (true) {
		mt.lock();
		q.push(i++);
		mt.unlock();  //  если б забыли unlock сделать, возникает блокировка.  И оба потока заблокаются, это deadlock

		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


void consume() {
	/*  // часть с прошлого примера (начало в предыдущем проекте)
	mt.lock();
	std::cout << value << std::endl;
	mt.unlock();
	*/


	while (true) {
		mt.lock();
		if (not q.empty()) {
			auto value = q.front();

			q.pop();

			std::cout << value << std::endl;
		}
		mt.unlock();
	}
}



/*
	Чтобы не забывать писать lock/unlock, то можно сделать раишный подход. Прекрасный юзкейс, когда в конструкторе делаем lock, а в деструкторе unlock.

	Для этого есть специальные механизмы, например lockguard. 
*/


int main(int args, const char* argv[]) {

	std::thread tr1{ produce };
	std::thread tr2{ consume };


	tr1.join();
	tr2.join();



	return 0;
}