#include <iostream>
#include <memory> 


// RAII

int main(int argc, const char* argv[]) {

	int* ptr = new int; // MP -> allocator(malloc)
	delete ptr; // MP -> free


	std::unique_ptr<int> ptr1{ new int{10} }; // создаём как объект, но работаем как с обычным указателем. ptr1 имеет в private 2 поля:
											  // T* ptr1; Deleter del;
	*ptr1 = 100; 


	// auto ptr_new = ptr1; // объект unique_ptr нельзя присвоить другому (т.е. банальное копирование). У него все конструкторы копирования запрещены
	
	std::unique_ptr<int> ptr_new = std::move(ptr1); // объекты unique_ptr могут быть только перемещаемы. По сути ресурс( new int{10}), 
													// которым владел ptr1, мы перенесли в  ptr_new. ptr1 становится valid but unspecified state

	if (ptr1 == nullptr) {
		std::cout << "ptr1 (before reset) = nullptr\n";
	}

	ptr1.reset(new int{ 100 }); // заново присвоем новое значение, можно резет делать и перед мувом, тогда он сначала освободит память, 
								// а потом присвоит новую

	
	/*[ptr1]() {  так ошбика copyable нет

	}();*/

	[ptr1 = std::move(ptr1)]() {  // чтобы в контекст лямбды передать, то надо замувать
		
	}();
	

	system("pause");
	return 0;
}