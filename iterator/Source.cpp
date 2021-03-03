#include <iostream>
#include <vector>
#include <list>




int main(int argc, const char* argv) {

	std::vector v{1, 2, 3};

	auto it{ v.begin() };

	std::cout << *it << std::endl;

	*it = 100;
	++it;
	--it;

	std::cout << *(it + 2) << std::endl; 

	if (it + 3 == v.end()) {
		std::cout << "end\n";
	}
	
	{
		std::list<int> l{ 1,2,3 };

		auto it_{ l.begin() };

		std::cout << *it_ << std::endl;

		*it_ = 100;
		//++it_;
		//--it_;

		// std::cout << *(it_ + 2) << std::endl; // в list понятно так сделать нельзя, ибо ноды расположены хаотично в памяти 

		std::advance(it_, 2); // смещает итератор на 2 позиции. получает итератор по ссылке и увеличивает его 
		std::cout << *it_ << std::endl;

		if (std::next(l.begin(), 3) == l.end()) {  // next увеличивает итератор и возвращает его как новый итератор
			std::cout << "end\n";
		}



		auto dis{ std::distance(l.begin(), l.end()) }; // к-ство элементов лежищих между этими итераторами

		std::cout << dis << std::endl;
		


		auto it_1{ l.begin() };
		++it_1;
		std::cout << *it_1 << std::endl; // получим 2

		std::list<int>::reverse_iterator it_r{ it_1 };
		std::cout << *it_r << std::endl; // получим 100 (первый элемент списка)

		auto bs{ it_r.base() };
		std::cout << *bs << std::endl;  // получим 2

	}


	system("pause");
	return 0;
}