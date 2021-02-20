#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>


class Account {
public:
	void add(int count) {}
	void del(int count) {}
	std::mutex mt;
};


void transfer(Account& user1, Account& user2) {
	/*
	user1.mt.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));  // между этими двумя строками, тут может происходить n действий
	user2.mt.lock();
	
	
		// Всё вроде гуд, но тут deadlock! Сначала поток tr1 для user1 залочил мьютекс, потом поток tr2 для user2 залочил
		// мьютекс, затем tr1 пытается залочить мьютекс для user2, но не может и tr2 пытается залочить для user1 и также не может.

		// Нам нужно синхронизировать порядок локов между потоками. И есть готовое решение std::lock. Чтобы не было взаимной блокировки - он сам 
		// определит правильный порядок локов для каждого из этого мьютекса.
		
		// lock_guard добавим чтобы unlock не писать. И в lock_guard нам уже не нужно блокировать поэтому пишем std::adopt_lock
		// или unique_lock добавить можно, и тег std::defer_lock. И нужно в начало вынести.
	 
	user1.add(100);
	user2.del(100);

	user2.mt.unlock();
	user1.mt.unlock();
	*/


	// std::unique_lock<std::mutex> l1{ user1.mt, std::defer_lock };
	// std::unique_lock<std::mutex> l2{ user2.mt, std::defer_lock };

	std::lock(user1.mt, user2.mt);
	std::lock_guard<std::mutex> l1{ user1.mt, std::adopt_lock };
	std::lock_guard<std::mutex> l2{ user2.mt, std::adopt_lock };

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	user1.add(100);
	user2.del(100);
}


int main(int args, const char* argv[]) {

	Account user1;
	Account user2;

	std::thread tr1{transfer, std::ref(user1), std::ref(user2)};
	std::thread tr2{transfer, std::ref(user2), std::ref(user1)};


	tr1.join();
	tr2.join();



	return 0;
}