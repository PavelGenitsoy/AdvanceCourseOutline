#include <iostream>
#include <array>
#include <functional>


bool is_even(int div, int value) {  // хотим чтобы ф-ция вела себя как функтор
	std::cout << "div = " << div << "  &  " << "value = " << value << std::endl;
	return value % div == 0;  
}


template <typename T, typename T1>
T find_(T begin, T const end, T1 func) {
	while (begin != end + 1)
	{
		if (func(*begin)) { 
			return begin;
		}
		++begin;
	}
	return end;
}


int main(int argc, const char* argv[]) {

	std::array arr{ 1, 5, 1, 4 };

	auto fun = std::bind(is_even, 5, std::placeholders::_1);  // мы байндим к ф-ции is_even значение 5 как первый аргумент, а следующий  
															  // аргумент должен передаватся как значение. Мы с бинарной ф-ции сделали унарную 
	auto it = find_(&arr[0], &arr[arr.size() - 1], fun); 

	/*
		std::bind это overhead, std::function это как улучшенный std::bind
	*/

	system("pause");
	return 0;
}