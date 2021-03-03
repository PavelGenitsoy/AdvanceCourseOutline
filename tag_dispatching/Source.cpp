#include <iostream>
#include <list>
#include <iterator>
#include <vector>


template<typename InputIt, typename Distance>
void advance(InputIt& begin, Distance n, std::forward_iterator_tag) { 
	std::cout << "forward\n";
	while (n--) {
		++begin;
	}
}


template<typename InputIt, typename Distance>
void advance(InputIt& begin, Distance n, std::bidirectional_iterator_tag) {
	std::cout << "bidirectional\n";
	if (n > 0) {
		while (n--) {
			++begin;
		}
		return;
	}
	while (n--) {
		++begin;
	}
}


template<typename InputIt, typename Distance>
void advance(InputIt& begin, Distance n, std::random_access_iterator_tag) {
	std::cout << "random_access\n";
	begin += n;
}


// vector
template<typename InputIt, typename Distance>
void advance(InputIt& begin, Distance n) {
	advance(begin, n, typename std::iterator_traits<InputIt>::iterator_category()); // через iterator_traits получаем какой категории наш итератор
}


int main(int argc, const char* argv) {

	std::list<int> l{ 1,2,3, };

	auto it{ l.begin() };

	// advance(it, 2); // it +=2; // for (2) {++it;} 


	int arr[10];

	auto it_a{ std::begin(arr) };


	
	// std::vector v{ l.begin(), l.end() }; // copy
	std::vector v{ std::make_move_iterator(l.begin()), std::make_move_iterator(l.end()) }; // move



	system("pause");
	return 0;
}