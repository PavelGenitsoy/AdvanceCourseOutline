#include <iostream>
#include <type_traits>


template <typename T>
struct remove_ptr {
	typedef T type; // алиас на другой тип, но это устаревший вид 
	// using type = T; // вот по новому
};

template <typename T>
struct remove_ptr <T*> {
	typedef T type; 
};

/*
template <typename T>
void f_test1(T data) {
	remove_ptr<T>::type value{};
}
*/

template <typename T>
void f_test(T data) {
	typename remove_ptr<T>::type value{};
}

int main(int argc, const char *argv[]) {

	std::cout << std::boolalpha;

	remove_ptr<int*>::type value;  // int* -> int

	int b;
	int* a = &b;
	// f_test1(a);  // error
	f_test(a);

	system("pause");
	return 0;
}