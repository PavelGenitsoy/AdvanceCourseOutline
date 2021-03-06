#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <string>



int main(int argc, const char* argv[]) {

	std::list<int> l{ 1, 2, 2, 4 };

	std::vector<int> v;

	std::copy_if(l.cbegin(), l.cend(), std::back_inserter(v), [](auto value) {  // back_inserter это как итератор адаптер, под капотом делается pushback
		return value % 2 == 0;
	});

	for (const auto& var : v) {
		std::cout << var << " ";
	}
	std::cout << std::endl;


	std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " -> ")); // таким способ можно выводить на экран
	std::cout << std::endl;
	

	/////////////////////////////////////////


	std::string str{ "hello world" };

	std::transform(str.cbegin(), str.cend(), str.begin(), toupper);  // to upper register without loops
							// т.е. мы тут берём входную посл-сть модифицируем каждое значение ф-цией(toupper) и записываем её в ту же самою строку

	std::cout << str << std::endl;


	///////////////////////////////////////


	std::vector<int> v1{1,2,3,2,5,10};

	auto it = std::remove(v1.begin(), v1.end(), 2); // размер посл-сти не измениться (в хвосте появиться 2 значение которые даже не двойки (мусор))

	std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " -> ")); // таким способ можно выводить на экран
	std::cout << std::endl;

	std::cout << std::distance(v1.begin(), it) << std::endl;


	v1.erase(it, v1.end()); // всё то что находиться с итератора нового конца до конца последовательности v1 мы удаляем

	std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " -> ")); 
	std::cout << std::endl;



	system("pause");
	return 0;
}