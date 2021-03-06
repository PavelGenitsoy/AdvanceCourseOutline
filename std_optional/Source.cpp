#include <iostream>
#include <optional>
#include <variant>


std::pair<bool, int> get() { // до появления optional
	return { false, 10 };
}


std::optional<int> get_int() {
	return { 10 };  // если ф-ция возвращает ошибку то возвращаем std::nullopt
}


int main(int argc, const char* argv[]) {

	if (auto data{ get_int() }; data != std::nullopt) { // если тут не будет проверки на nullopt и оно попадётся, то будет exception
		std::cout << data.value() << std::endl; 
		std::cout << *data << std::endl; // или так
	}

	//////////////////////////////////


	/*
		Тип variant - это безоапсный union(объединение). Все переменные, которые объявлены в union, разделяют между собой одну и ту же память. 
		А размер union будет определяться размером самой максимальной переменной. 

		variant означает, что в 1 какой-то момент времени мы храним 1 какое-то значение. 

		variant удобно обрабатывать с помощью std::visit
	*/

	std::variant<int, double> v;

	v = 10;

	// double d = std::get<1>(v);  // кинется exception. Ибо у нас есть значение по int, а прочитать хотим как double





	system("pause");
	return 0;
}