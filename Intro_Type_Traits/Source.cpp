#include <iostream>
#include <string>
#include <type_traits>


/*
template <typename T>
auto to_string(T data) -> std::string { // std::string пишут для понимания (и если пишем объявление в заголовочном файле)
	return std::to_string(data);
}
*/

template <typename T>
auto to_string(T data) { // std::string пишут для понимания
	static_assert(not std::is_same<T, const char*>::value, "const char*!!!!");
	return std::to_string(data);
}

int main(int argc, const char *argv[]) {
	
	auto str{ to_string(10) };  // int -> string
	
	// auto str1{ to_string("Hello char") };  // если передаём char array (т.е. const char*), то ошибка   

	int a;
	int* ptr = &a;
	std::remove_pointer<int*>::type variable = 100;  // указатель делитнули

	system("pause");
	return 0;
}