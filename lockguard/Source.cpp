#include <iostream>
#include <thread>
#include <mutex>
#include <queue>


int value{ 10 };
bool flag{ false };

std::mutex mt;
std::queue<int> q;

void produce() {

	static int i{}; 
	while (true) {

		{
			std::lock_guard<std::mutex> l{ mt };  // когда объект будет выходить из области видимости, то вызовется unlock(в деструкторе), а в конструкторе lock
			q.push(i++);
		}

		// .....
		//std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}


void consume() {

	while (true) {
		// std::lock_guard<std::mutex> l{ mt };
		std::unique_lock<std::mutex> l{ mt, std::defer_lock };  // мьютекс желательно нужно сужать, плохо когда они захватывают всю область видимости, поэтому можно 
											  // использовать unique_lock - это уже врапер вокруг мьютекса, он не только захватывает и освобождает
											  // ресурс как lock_guard, но ещё позволяет использовать lock and unlock руками   !мьютекс это дорого!

		while (not l.try_lock()) {  // пока не захватим мьютекс, будем крутится в этом цикле
			std::cout << "Hello\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		if (not q.empty()) {
			auto value = q.front();

			q.pop();
			l.unlock();
			// release mutex

			std::cout << value << std::endl;
		}
	}
}



int main(int args, const char* argv[]) {

	std::thread tr1{ produce };
	std::thread tr2{ consume };


	tr1.join();
	tr2.join();



	return 0;
}