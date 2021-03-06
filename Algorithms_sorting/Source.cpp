#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <string>



int main(int argc, const char* argv[]) {

	std::list<int> l{ 1, 2, 2, 4 };
	std::vector<int> v{ 7, 2, 3, 2, 5, 10 };

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " -> "));
	std::cout << std::endl;

	std::nth_element(v.begin(), v.begin() + 4, v.end()); // интересует элемент который будет находиться на 4-той позиции, толкьо на clang or gcc работает как надо

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " -> "));
	std::cout << std::endl;


	system("pause");
	return 0;
}