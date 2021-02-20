#include <iostream>
#include <thread>
#include <mutex>


// std::mutex mt;
std::recursive_mutex rmt;

void recursive(int& count) {
	// std::lock_guard<std::mutex> l{ mt }; // Здесь будет deadlock ибо мы лочим мьютекс, но не делаем unlock ему. Поэтому можем использовать рекурсивный мьютекс
	
	std::lock_guard<std::recursive_mutex> l{ rmt };
	if (count == 10)
		return;

	recursive(++count);
}


int main(int args, const char* argv[]) {

	int count{};

	std::thread tr1{ recursive, std::ref(count) };
	std::thread tr2{ recursive, std::ref(count) };


	tr1.join();
	tr2.join();


	return 0;
}