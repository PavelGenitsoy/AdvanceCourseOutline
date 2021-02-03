#include <iostream>
#include <memory>


/*
	Фабричные ф-ции:
		std::make_unique    позволяет создавать unique_ptr
		std::make_shared	позволяет создавать shared_ptr
*/


void get_pointer(std::unique_ptr<int> ptr1, std::unique_ptr<int> ptr2) {
	// .....
}


int main(int args, const char* argv) {
	
	std::unique_ptr<int> ptr1{ new int{} };  
	std::unique_ptr<int> ptr2{ new int{} };

	get_pointer(std::move(ptr1), std::move(ptr2));

	/*
		но лучше же создавать два эти unique_ptr при вызове ф-ции.
		
		std::unique_ptr<int> ptr1{ new int{} }   этот процесс разделяется на 2 процесса: выделение памяти и создание объекта unique_ptr
	*/

	/*
	get_pointer(new int{ 100 }, new int{ 150 });  // здесь компилятор в процессе вызова ф-ции может делать различные юзкейсы, т.е.:

	я могу сначала выделить ресурс new int{ 100 }, дальше создать объект std::unique_ptr 1, дальше снова выделяю ресурс new int{ 150 }
	и создую объект std::unique_ptr 2   (это идеальный юзкейс). Т.е. здесь, если new int{ 150 } кинул exception, то я точно разрушу
	первый созданный объект. И у меня не будет memory leak.

	(ПОРЯДОК ВЫЧИСЛЕНИЯ АРГУМЕНТОВ ПРИ ВЫЗОВЕ Ф-ЦИИ ДО С++17 ЯВЛЯЛСЯ НЕОПРЕДЕЛЁННЫМ)

	НО !!! Если будет иная ситуация: сначала будет выделятся ресурс под 2 объекта, а потом эти объекты будут конструироватся. И если
	теперь снова какой-то unique_ptr кинул эксепшен, например new int{ 150 } -> exception, то это new int{ 100 } будет memory leak, ибо 
	мы ещё не создали unique_ptr, который освободит этот ресурс.

	Фиксится это с помощью ФАБРИЧНЫХ Ф-ЦИЙ - т.е. ф-ция которая возвращает вам завершённый объект. memory leak никак не произойдёт
	*/

	get_pointer(std::make_unique<int>(100), std::make_unique<int>(150)); // собственно с фабричными ф-циями



	system("pause");
	return 0;
}