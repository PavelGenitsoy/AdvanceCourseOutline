#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <string>



int main(int argc, const char* argv[]) {

	std::list<int> l{ 1, 2, 2, 4 };
	std::vector<int> v{ 1, 2, 3, 2, 5, 10 };

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " -> "));
	std::cout << std::endl;

	auto it = std::partition(v.begin(), v.end(), [](auto value) {  // в левой половине посл-сти элементы что удовлетворяют условию, в правой - не удовлетворяют
		return value % 2 == 0;
	});

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " -> "));
	std::cout << std::endl;

	std::copy(v.begin(), it, std::ostream_iterator<int>(std::cout, " -> "));
	std::cout << std::endl;




	system("pause");
	return 0;
}