#include <iostream>
#include <string>


void* operator new(size_t count) {
	std::cout << "new\n";
	return malloc(count);
}


// void test(const std::string& str) {} // так делали раньше, а после с++17 стали юзать string_view

void  test(std::string_view str) {} // good


int main(int argc, const char* argv) {

	/*
		Под капотом string юзает small string optimisation, т.е. под небольшие строки не выделяет память (работает в компиляторах gcc, clang.  На винде не пашит)

		Псевдокод string:

			class string {
				private:
					char small_str [10]; // например 10, если размер строки не превышал 10, то он хрнаился в массиве, иначе выделяется память
					char* str;
			}
	*/

	std::string str{ "123" }; 

	// std::string str1{ "" }; // bad
	// std::string str2{}; // good 


	system("pause");
	return 0;
}