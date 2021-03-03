#include <iostream>
#include <list>
#include <iterator>



int main(int argc, const char* argv) {

	std::ostream_iterator<int> writer(std::cout, "\n");

	*writer = 200;

	++writer;

	*writer = 300;






	system("pause");
	return 0;
}