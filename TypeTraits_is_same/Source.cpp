#include <iostream>
#include <type_traits>


template <typename T1, typename T2>
struct is_same {   // этот use keys работает тогда, когда Т1 и Т2 разные
	// enum{value = false};  // это старая запись
	static constexpr bool value{ false };
};

template <typename T1>
struct is_same <T1, T1> {   // этот use keys работает тогда, когда Т1 и Т2 одинаковые
	static constexpr bool value{ true };
};

int main(int argc, const char *argv[]) {

	std::cout << std::boolalpha;

	std::cout << is_same<int, int>::value << std::endl;
	std::cout << is_same<int, bool>::value << std::endl;


	system("pause");
	return 0;
}