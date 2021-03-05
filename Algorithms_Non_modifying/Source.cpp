#include <iostream>
#include <algorithm>
#include <vector>
#include <list>





int main(int argc, const char* argv[]) {

	std::list<int> l{ 1, 2, 2, 4 };
	std::list<int> l1{ 1, 5, 3, 7 };

	//auto status = std::any_of(l.cbegin(), l.cend(), [](const auto& value) { // если алгоритм который не модифицирует п-сть, то лучше передавать константный итератор
	//	return value % 2 == 0;
	//}); 

	auto status = std::all_of(l1.cbegin(), l1.cend(), [](const auto& value) { 
		return value % 2 == 1;
	});

	/*
	Так std::all_of выглядит по сути:

		bool not_ = false;
		for() {
			if(element) {
				not_ = true;
				break;
			}
		}
	*/

	if (status) {
		std::cout << "ok status\n";
	}
	else {
		std::cout << "not ok\n";
	}


	/////////////////////////////////////////


	auto status2 = std::count(l.cbegin(), l.cend(), 2);

	std::cout << "count of 2 in l = " << status2 << std::endl;

	auto status3 = std::count_if(l.cbegin(), l.cend(), [](const auto& value) { // count_if ибо мы используем компоратор
		return value % 2 == 0;
	});

	std::cout << "count of even num in l = " << status3 << std::endl;


	///////////////////////////////////////


	auto status4 = std::adjacent_find(l.cbegin(), l.cend());


	if (status4 != l.cend()) {
		std::cout << std::distance(l.cbegin(), status4) << std::endl;
	}

	auto status5 = std::adjacent_find(l.cbegin(), l.cend(), [](auto rhs, auto lhs) { // analog is_sorted;   бинарный предикат тут
		return rhs > lhs;
	});

	if (status5 != l.cend()) {
		std::cout << "unsorted\n";
	}


	system("pause");
	return 0;
}