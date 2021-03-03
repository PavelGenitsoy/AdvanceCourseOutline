#include <iostream>
#include <list>
#include <iterator>



int main(int argc, const char* argv) {

	std::list<int> l{ 1,2,3 };

	std::back_insert_iterator<std::list<int>> iter{ l }; // итератор-адаптер. Т.е. когда мы делаем присвоение (*iter = 200), наш класс-адаптер для
														 // своего присвоения вызывает для контейнера (list) push_back операцию, которая соответственно
														 // модифицирует контейнер, который мы сюда и передали


	*iter = 100; // push_back под капотом
	for (const auto& var : l) {
		std::cout << var << " ";
	}
	std::cout << "\n";


	//++iter;
	*iter = 200; // push_back
	for (const auto& var : l) {
		std::cout << var << " ";
	}
	std::cout << "\n";


	std::back_inserter(l) = 300; // явное добавления(push_back) элемента в контейнер 
	for (const auto& var : l) {
		std::cout << var << " ";
	}
	std::cout << "\n";

	

	system("pause");
	return 0;
}