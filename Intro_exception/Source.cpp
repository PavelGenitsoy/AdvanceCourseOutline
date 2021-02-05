#include <iostream>
#include <exception>


/*
	В первую очередь exception должен быть сгенерирован (для генерации используется throw), следующим (после throw) идёт выражение, которое 
	представляет собой одного из наследников std::exception.

	throw это некий return (но не обычной ф-ции), т.е. то, что после throw происходит - не будет ниокгда выполнено
*/


void generate_exception() {
	throw std::runtime_error{"runtime_error"};  // сгенерировали исключительную ситуацию и дальше по стеку вызова ф-ции ищем ближайший catch блок 
	std::cout << "end void func\n";
} // если нет обработчика этой исключительной ситуации, то вызывается std::terminate, которое делает abort, т.е. прерывание выполнения программы


void generate_exception1() {
	throw std::logic_error{ "logic_error" }; 
	std::cout << "end void func\n";
}


int main(int args, const char* argv[]) {

	try {
		//generate_exception();
		generate_exception1();
	}
	catch (std::runtime_error& ex) {	//  catch будет захватывать тот exception, который сгенерировали
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception& ex) {  //  этот юзкейс ставят только тогда, когда произошёл неожидаемый exception
		std::cout << ex.what() << std::endl;
	}
	catch (...) {  //  этот юзкейс ставят когда exception ничего общего не имеет с наследниками std::exception
		std::cout << "generic error\n";
	}

	std::cout << "continue main_func\n";


	system("pause");
	return 0;
}