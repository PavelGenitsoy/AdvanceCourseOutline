#include <iostream>
#include <array>


void func(const std::array<int, 10>& arr) {}


int main(int argc, const char* argv) {

	// int arr[argc]; // это расширение компилятора, массивы можно делать перемнной длины (сишные массивы)
	std::array<int, 10> arr{ 1,2,3 };

	// std::array<std::array<int, 10>, 10> arr{1,2};

	std::array<int, 10> arr_{ std::move(arr) }; // copy



	return 0;
}