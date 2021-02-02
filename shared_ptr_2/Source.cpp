#include <iostream>
#include <memory>


void* operator new(size_t size) {
	std::cout << "alloc\n";
	return malloc(size);
}


int main(int args, const char* argv) {

	std::weak_ptr<int> wptr; 

	{
		std::shared_ptr<int> ptr{ new int {10} };
		/*
		Когда создаём shared_ptr у нас происходит 2 алокации. Что это за алокации??
		*/


		wptr = ptr;
		std::cout << wptr.use_count() << std::endl;
		if (auto ptr_inner = wptr.lock()) { // если wptr говорит, что ресурс существует, то мы получим валидный shared_ptr на этот ресурс
			*ptr_inner = 1000;
		}

		std::cout << "*ptr = " << *ptr << std::endl;
	}

	if (wptr.expired()) { // будем использовать для проверки: владеет ли ptr ещё ресурсом?
		std::cout << "generic scope::expired\n";
	}


	system("pause");
	return 0;
}