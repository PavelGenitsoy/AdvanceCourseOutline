#include <iostream>
#include <memory>


void* operator new(size_t size) {
	std::cout << "alloc\n";
	return malloc(size);
}


void operator delete(void* ptr) {
	std::cout << "delete\n";
	free(ptr);
}


class advance {
public: 
	advance() {
		std::cout << "ctr\n";
	}
	~advance() {
		std::cout << "dtr\n";
	}
};


int main(int args, const char* argv) {

	// std::shared_ptr<int> ptr{ new int{15} };  // 2 раза выведится alloc , и 2 раза выведится delete. Чтобы это увидеть через cmd запусти .exe файл
												 // output: alloc, alloc, delete, delete


	// std::shared_ptr<int> ptr{ std::make_shared<int>(15) }; // 1раз alloc(control object, control block компилятор будет под них 1 алокацию 
														   // делать, т.е. как целый блок выделять) и 1раз delete. Круто, но есть подводные камни.
														   // output: alloc, delete


	// std::shared_ptr<advance> ptr{ std::make_shared<advance>() }; // output: alloc, ctr, dtr, delete 


	// std::shared_ptr<advance> ptr{ new advance{} }; // output: alloc, ctr, alloc, dtr, delete, delete

	/*
	std::weak_ptr<advance> w_ptr;
	{
		std::shared_ptr<advance> ptr{ new advance{} };
		w_ptr = ptr;
	}												  // output: alloc, ctr, alloc, dtr, delete, intermediate log....., delete       
	std::cout << "intermediate log.....\n";
	*/


	std::weak_ptr<advance> w_ptr;
	{
		std::shared_ptr<advance> ptr{ std::make_shared<advance>() };
		w_ptr = ptr;
	}												  // output: alloc, ctr, dtr, intermediate log....., delete       
	std::cout << "intermediate log.....\n";
	
	/*
		как мы видим, что после выхода из области видимости, объект ptr память за собой не очищает, он вызывает деструктор для ресурса,
		но память внутри блока(что идёт под control object, control block как одно целое) будет уже освобождена когда последний w_ptr
		покинет область видимости. И... 
		
		ПРОБЛЕМА если advance - огромен. И по факту вы как бы вызвали деструктор (какие-то объекты разрушились), 
		но сам по себе класс(который в памяти) он не разрушился, а продолжает занимать место в хипе(heap).
	*/


	return 0;
}