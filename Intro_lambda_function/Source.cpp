#include <iostream>
#include <array>


/*
	Перед лямбда ф-циями разберём одну задачку!
*/

// обычный алг. поиска

using Func =  bool(*)(int);  // т.е. Func собой представляет тип, который является указателем на ф-ции

// тут с конкретным типом
//int* find_(int* begin, int* const end, Func func) {
//	while (begin != end + 1)
//	{
//		if (func(*begin)) {
//			return begin;
//		}
//		++begin;
//	}
//	return end;
//}


// теперь для шаблонов, тут гараздо приятнее передовать указатели на ф-ции
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

bool is_even(int value) {  // bool (int)
	return value % 2 == 0;
}


int main(int argc, const char* argv[]) {

	// std::array<int, 4> arr{1, 2, 3, 4};
	std::array arr{ 1, 1, 3, 4 };

	auto it = find_(&arr[0], &arr[arr.size() - 1], is_even); // а если бы хотели получить число которое делится по модуля 2. то надо передовать в ф-цию предикат


	if (it == &arr[arr.size() - 1] + 1) {
		std::cout << "Not found\n";
	}
	else {
		std::cout << *it << std::endl;
	}
	

	system("pause");
	return 0;
}