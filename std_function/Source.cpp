#include <iostream>
#include <array>
#include <functional>


class Functor {
public:
	Functor(int data) : data{ data } {}

	bool operator() (int value) {
		std::cout << "hello" << std::endl;
		return value % data == 0;
	}

private:
	int data{};   
};


int* find_(int* begin, int* const end, std::function<bool(int)> func) { // type eraser , т.е. стирание типов.  Её стоит избегать!!
																		// простое понятие его: контейнер на ф-ции
	while (begin != end + 1)
	{
		if (func(*begin)) {
			return begin;
		}
		++begin;
	}
	return end;
}


bool is_even(int value) {
	return value % 2 == 0;  
}


int main(int argc, const char* argv[]) {

	std::array arr{ 1, 5, 1, 4 };

	auto it = find_(&arr[0], &arr[arr.size() - 1], is_even);  // work without errors, but i have no output...
	std::cout << "///////////////\n";
	auto it_ = find_(&arr[0], &arr[arr.size() - 1], Functor{ 5 }); 	// work

	std::cout << "Size of class functor: " << sizeof(Functor) << "\nSize of pointer: " << sizeof(&is_even) << std::endl;

	system("pause");
	return 0;
}