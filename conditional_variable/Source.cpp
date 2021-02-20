#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>


int value{ 10 };
bool flag{ false };

std::mutex mt;
std::queue<int> q;
std::condition_variable cv;

void produce() {

	static int i{};

		{
			std::lock_guard<std::mutex> l{ mt };  
			q.push(i++);
			cv.notify_one(); // (notified) уведомили поток consume, чтобы он вышел из состояния wait, а при выходе из wait снова будет проверятся предикат
		}

}


void consume() {

	while (true) {
		{
			std::unique_lock<std::mutex> l{ mt };


			// std::this_thread::yield(); // говорит что дальнейшие операции, которые будут например ниже, к примеру они будут IO операции и время которое 
										  // было доступно для этого мы можем передать другому потоку для эфективного использования. Удобно в async


			cv.wait(l, []() { return not q.empty(); }); // здесь мы устанавливаем проверку, т.е. мы не будем исполнять ниже код, пока условие в предикате не 
														// станет истинной. Пока предикат - false, то мы блокируемся, и ждём пока нас кто-то не уведомит, что
														// в очереди есть задача. Соответственно кто-то должен нас пробудить (это наш поток produce)

			std::cout << "some text\n";

			auto value = q.front();
			std::cout << value << std::endl;
			q.pop();
		}

		std::cout << value << std::endl;

	}
}



int main(int args, const char* argv[]) {

	std::thread tr1{ consume };
	std::thread tr2{ produce };


	tr1.join();
	tr2.join();



	return 0;
}