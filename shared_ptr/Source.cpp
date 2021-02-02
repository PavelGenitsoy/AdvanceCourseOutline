#include <iostream>
#include <memory>


void del(int* ptr) {
	delete ptr;
}


int main(int args, const char* argv) {

	std::shared_ptr<int> ptr{ new int {10} };  // способ(синтаксис) создания аналогичен unique_ptr, а способ работы отличается
											   // счётчик ссылок 1

	{
		std::shared_ptr<int> ptr1 = ptr; // оба ссылаются на один и тот же ресурс
										 // счётчик ссылок 2
		std::cout << *ptr << std::endl;
		*ptr1 = 100;
		std::cout << "Local scope. Quantity of ref = " << ptr.use_count() << std::endl;
	}

	std::cout << *ptr << std::endl;

	std::cout << "Generic scope. Quantity of ref = " << ptr.use_count() << std::endl; 

	std::cout << "Sizeof(ptr) = " << sizeof(ptr) << std::endl; // размер двух указателей
	

	std::shared_ptr<int> ptr2{ new int {50}, del };
	std::cout << "Sizeof(ptr2) = " << sizeof(ptr2) << std::endl; // размер не изменился



	system("pause");
	return 0;
}