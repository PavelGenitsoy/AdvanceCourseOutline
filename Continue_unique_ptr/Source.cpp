#include <iostream>
#include <memory> 
#include <stdio.h>

/* // дефолтная реализация делитера
class Deleter {
public:
	void operator()(void* ptr) {
		delete ptr;
	}
};
*/

void operator delete(void* ptr) {
	std::cout << "delete\n";
	free(ptr);
}


int main(int argc, const char* argv[]) {

	std::unique_ptr<int> ptr{ new int{10} };

	std::cout << "Size of unique_ptr ptr = " << sizeof(ptr) << std::endl; // размер обычного указателя, т.е. память под Deleter не выделяется
																	  // ибо он не имеет состояния. Deleter это функтор, который имеет
																   // перегруженный оператор вызова ф-ции. А почему не с помощью просто delete??

	/*
	FILE* file{ fopen("hello", "w+") }; // СИшная конструкция. создали ресурс файл. Т.е. мы тут что-то выделяли(файл), и получили указатель на этот ресурс

	if (file != nullptr) {
		// ....fread/fwrite
		fclose(file);  // здесь освобождаем ресурс файл (закрываем)
	}						// всю эту конструкцию можно переписать в unique_ptr
	*/

	// std::unique_ptr<FILE> ptr1{ fopen("hello", "w+") }; // T* ptr1; Deleter del;
	/*
		но получается 1 проблема: мы открыли файл, и вместо того чтобы закрыть его, используется delete. Надо указать кастомный делитер.
		т.е. сказать unique_ptr, что, вместо того чтобы он вызывал delete, вызывай ф-цию fclose. Поэтому передаём вторым параметром fclose.
		Но тогда и сам Deleter должен уже иметь сигнатуру самого fclose
	*/

	// Deleter -> int (*)(FILE *)      (т.е. указатель на эту ф-цию (fclose))
	std::unique_ptr<FILE, int(*)(FILE *)> ptr1{ fopen("hello", "w+"), fclose };  // теперь delete не вызываем, а вызываем fclose

	std::cout << "Size of unique_ptr ptr1 = " << sizeof(ptr1) << std::endl; // но теперь Deleter стал как указателем на ф-цию Deleter -> Deleter*
																			// поэтому размер в 2 раза больше (так как теперь 2 указателя)
																			// Как решить эту проблему???

	std::unique_ptr<FILE, decltype(&fclose)> ptr1_{ fopen("hello", "w+"), fclose }; // так для удобства пишут


	// РЕШЕНИЕ ПРОБЛЕМЫ: делать все кастомные делитеры через лямбда!!


	auto custom_del = [](FILE* file) { fclose(file); };

	std::unique_ptr<FILE, decltype(custom_del)> ptr_final{ fopen("hello", "w+"), custom_del };

	std::cout << "Size of unique_ptr ptr_final = " << sizeof(ptr_final) << std::endl; // снова размер одного указателя
	
	/*
		т.е. лямбда привела к тому, что мы сгенерировали класс (функтор делитер) у которого перегруженный оператор вызова ф-ции, 
		который под капотом оператору вызову ф-ции передаёт file как аргумент и внутри него вызывает fclose
	*/


	system("pause");
	return 0;
}